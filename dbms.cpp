#include "dbms.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

//初始化数据库配置
bool initdb(){
    QSqlDatabase db;
    if(!QSqlDatabase::contains("QSQLITE")){
        db=QSqlDatabase::addDatabase("QSQLITE");

        db.setHostName("127.0.0.1");
        db.setDatabaseName("epid-investDB.db");
        db.setUserName("root");
        db.setPassword("12345678");

        if(!db.open()){
            return false;
        }
    }
    else{
        db=QSqlDatabase::database("QSQLITE");
    }
    return true;
}

//主要的查询功能
struct finfo searchDB(struct finfo sfinfo, int &flag){
    QSqlQuery query;
    struct finfo rfinfo;

    QString trafficDate=sfinfo.trafficNum+' '+sfinfo.date;
    QString carriageNum=sfinfo.carriageNum;
    QString seatNum=sfinfo.seatNum;
    QStringList list=trafficDate.split(' ');

    QString q="select id from riskroute where traffic='"+list[0]+"' and date='"+list[1]+"' and carriageNum="+carriageNum;
    query.exec(q);
    if(!query.next()){//没有查询到高危，说明没有新冠患者接触史
        switch (sfinfo.type) {//判断所查询班次座位是否存在，若存在，flag不修改，若不存在，flag修改为相应错误码
        case TRAIN:
            //座位是否存在
            if(seatNum.toInt()>TRAIN_MAX_SEAT){
                flag=SEATERROR;
                break;
            }
            q="select carriage from train where trafficDate='"+trafficDate+"'";
            query.exec(q);
            //车次是否存在，如果查询结果为空，说明车次不存在
            if(!query.next()){
                flag=NOTRAFFIC;
            }
            else if(carriageNum.toInt()>query.value(0).toInt()){//车厢号是否存在
                flag=SEATERROR;
            }
            if(!inPasses(sfinfo.departure, sfinfo.destination,sfinfo.type,trafficDate)){
                flag=LOCATIONERROR;
            }//乘车区间是否正确
            break;
        case FLIGHT:
            if(seatNum.toInt()>FLIGHT_MAX_SEAT){
                flag=SEATERROR;
                break;
            }
            q="select * from flight where trafficDate='"+trafficDate+"'";
            query.exec(q);
            if(!query.next()){
                flag=NOTRAFFIC;
            }
            else
                flag=0;
            break;
        case BUS:
            if(seatNum.toInt()>BUS_MAX_SEAT){
                flag=SEATERROR;
                break;
            }
            q="select * from bus where trafficDate='"+trafficDate+"'";
            query.exec(q);
            if(!query.next()){
                flag=NOTRAFFIC;
            }
            else {
                flag=0;
            }
            break;
        case SHIP:
            if(seatNum.toInt()>SHIP_MAX_SEAT){
                flag=SEATERROR;
                break;
            }
            q="select * from train where trafficDate='"+trafficDate+"'";
            query.exec(q);
            if(!query.next()){
                flag=NOTRAFFIC;
            }
            else {
                flag=0;
            }
            break;
        }
    }
    else{//查询到高危，检查出发地和目的地是否存在途径表中，存在，则确实有高危，不存在，说明区间不正确
        flag=0;
        rfinfo.type=sfinfo.type;
        QString id=query.value(0).toString();
        if(!inPasses(sfinfo.departure, sfinfo.destination,sfinfo.type,trafficDate)){
            flag=LOCATIONERROR;
        }
        q="select pass from riskroute where id="+id;
        query.exec(q);
        if(query.next()){
            QString passes=query.value(0).toString();
            QStringList list=passes.split(' ',QString::SkipEmptyParts);
            rfinfo.departure=list[0];
            rfinfo.destination="";
            for(int i=0;i<list.length();i++){
                if(i!=list.length()-1){
                    rfinfo.destination.append(list[i]+" ");
                }
                else{
                    rfinfo.destination.append(list[i]);
                }
            }
        }
        q="select seatNum from riskroute where id="+id;
        query.exec(q);
        if(query.next()){
            rfinfo.seatNum=query.value(0).toString();
        }
    }
    return rfinfo;
}

//查询并判断输入是否在乘车区间内
bool inPasses(QString dept,QString dest,int type,QString trafficDate){
    QSqlQuery query;
    QString q,table;

    //选定交通工具类型，之后从表中查找
    switch (type) {
    case TRAIN:
        table="train";
        break;
    case FLIGHT:
        table="flight";
        break;
    case BUS:
        table="bus";
        break;
    case SHIP:
        table="ship";
        break;
    }
    q="select pass from "+table+" where trafficDate='"+trafficDate+"'";
    query.exec(q);

    //如果能够查询到，将查询到的区间列表保存在passes中，判断如果路径中包含出发地和目的地且出发和目的地不同，则在区间内
    if(query.next()){
        QString passes=query.value(0).toString();
        if(passes.contains(dept)&&passes.contains(dest)&&dept!=dest){
            return true;
        }
    }
    return false;
}

int insertDB(struct finfo ifinfo){
    int flag=NOERROR;
    QSqlQuery query;

    QString trafficDate=ifinfo.trafficNum+' '+ifinfo.date;
    QString carriageNum=ifinfo.carriageNum;
    QString seatNum=ifinfo.seatNum;
    QString departure=ifinfo.departure;
    QString destination=ifinfo.destination;

    QString q="insert into newrisk values ('"+trafficDate+"', '"+carriageNum+"', '"+
            seatNum+"', '"+
            departure+"', '"+
            destination+"')";
    //对不同类型交通工具查询是否存在此班次
    switch(ifinfo.type){
    case TRAIN:
        query.exec("select * from train where trafficDate = '"+trafficDate+"'");
        break;
    case FLIGHT:
        query.exec("select * from flight where trafficDate = '"+trafficDate+"'");
        break;
    case BUS:
        query.exec("select * from bus where trafficDate = '"+trafficDate+"'");
        break;
    case SHIP:
        query.exec("select * from ship where trafficDate = '"+trafficDate+"'");
        break;
    }

    if(!query.next()){//not exist
        flag = NOTRAFFIC;
    }
    else{
        query.exec(q);
    }

    return flag;
}

bool loginDB(QString id, QString key){
    QSqlQuery query;
    QString q="select key from admin where id ="+id;
    query.exec(q);
    if(query.next()){
        if(key==query.value(0).toString()){
            return true;
        }
    }
    return false;
}

QSqlTableModel* showDB(QString target){
    QSqlTableModel* model=new QSqlTableModel;
    model->setTable(target);
    model->select();
    return model;
}

bool addTrafficDB(QStringList list){
    QSqlQuery query;
    QString q,type;
    q="select traffic from traffic where traffic='"+list[0]+"'and date='"+list[2]+"'";
    query.exec(q);
    if(query.next()){//已存在
        return false;
    }
    else{
        q="insert into traffic values('"+list[0]+"','"+list[1]+"','"+list[2]+"','"+list[3]+"','"+list[5]+"')";
        query.exec(q);
        type=list[1];
        if(type=="火车"){
            q="insert into train values('"+list[0]+" "+list[2]+"','"+list[3]+"','"+list[4]+"','"+list[5]+"')";
        }else if(type=="飞机"){
            q="insert into flight values('"+list[0]+" "+list[2]+"','"+list[3]+"','"+list[5]+"')";
        }else if(type=="客车"){
            q="insert into bus values('"+list[0]+" "+list[2]+"','"+list[3]+"','"+list[5]+"')";
        }else{
            q="insert into ship values('"+list[0]+" "+list[2]+"','"+list[3]+"','"+list[5]+"')";
        }
        query.exec(q);
        return true;
    }
}

bool delTrafficDB(QStringList list){
    QSqlQuery query;
    QString q,type;
    q="select traffic from traffic where traffic='"+list[0]+"'and date='"+list[1]+"'";
    query.exec(q);
    if(!query.next()){
        return false;
    }
    else{
        q="delete from traffic where traffic='"+list[0]+"'and date='"+list[1]+"'";
        query.exec(q);
        type=list[2];
        if(type=="火车"){
            q="delete from train where trafficDate='"+list[0]+" "+list[1]+"'";
        }else if(type=="飞机"){
            q="delete from flight where trafficDate='"+list[0]+" "+list[1]+"'";
        }else if(type=="客车"){
            q="delete from bus where trafficDate='"+list[0]+" "+list[1]+"'";
        }else if(type=="轮船"){
            q="delete from ship where trafficDate='"+list[0]+" "+list[1]+"'";
        }
        query.exec(q);
        delNewRiskDB(list[0]+' '+list[1]);
        q="delete from riskroute where traffic='"+list[0]+"'and date='"+list[1]+"'";
        query.exec(q);
        return true;
    }
}

bool delNewRiskDB(QString trafficDate){
    QSqlQuery query;
    QString q;
    q="delete from newrisk where trafficDate='"+trafficDate+"'";
    return query.exec(q);
}

bool delRiskDB(QString id){
    QSqlQuery query;
    QString q;
    q="delete from riskroute where id="+id;
    return query.exec(q);
}

bool addtoRiskDB(QString trafficDate){
    QSqlQuery query;
    QString q,d;
    QStringList list;
    d=trafficDate;
    list=d.split(' ');

    q="select id from riskroute where traffic='"+list[0]+"' and date='"+list[1]+"'";
    query.exec(q);
    if(!query.next()){
        q="select * from newrisk where trafficDate='"+trafficDate+"'";
        query.exec(q);
        if(query.next()){
            QString traDate=query.value(0).toString();
            QString carriageNum=query.value(1).toString();
            QString seatNum=query.value(2).toString();
            QString departure=query.value(3).toString();
            QString destination=query.value(4).toString();
            QString type;

            if(trafficDate[0].isLetter()&&trafficDate[1].isLetter()){
                type="飞机";
                carriageNum='1';
            }
            else{
                QChar a=trafficDate[0];
                switch (a.unicode()-'A') {
                case 0://bus Axxxx
                    type="客车";
                    carriageNum='1';
                    break;
                case 1://ship Bxxxx
                    type="轮船";
                    carriageNum='1';
                    break;
                default://train
                    type="火车";
                    break;
                }
            }
            q="delete from newrisk where trafficDate='"+trafficDate+"'";
            query.exec(q);
            q="insert into riskroute values(NULL,'"+list[0]+"','"+type+"','"+list[1]+"',"+carriageNum+","+seatNum+",'"+departure+' '+destination+"')";
            query.exec(q);
            return true;
        }
        return false;
    }
    else{
        //wrong,exists
        return false;
    }
}
