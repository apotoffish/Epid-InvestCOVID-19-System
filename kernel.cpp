#include "kernel.h"

int riskCompute(struct finfo rfinfo,struct finfo sfinfo)
{
    int risk=0;
    int r=rfinfo.seatNum.toInt();
    int s=sfinfo.seatNum.toInt();

    //先检查乘车区间是否相交，不相交，risk=0返回，否则继续计算。
    if(!isInterval(rfinfo,sfinfo)){
        return risk;
    }

    //如果区间相交进入计算风险等级，该等级根据
    //《新型冠状病毒肺炎病例密切接触者调查与管理指南》
    //中新冠肺炎病例密切接触者的判定原则判定风险等级
    risk=riskLevel(rfinfo.type,r,s,risk);

    return risk;
}

bool isInterval(struct finfo rfinfo,struct finfo sfinfo){
    QString riskInterval=rfinfo.destination;
    if(riskInterval.endsWith(sfinfo.departure)||riskInterval.startsWith(sfinfo.destination)){
        //没有交集，无风险
        return false;
    }
    else if(riskInterval.contains(sfinfo.departure)||riskInterval.contains((sfinfo.destination))){
        return true;
    }
    else{//没有交集，无风险
        return false;
    }
}

int riskLevel(int type,int r,int s,int &risk){
    int rrow,srow;

    switch (type) {
    case 0:
        return risk;
    case TRAIN://同排5人，从1开始
        rrow=r/5;
        srow=s/5;
        break;
    case FLIGHT://
        rrow=r/6;
        srow=s/6;
        break;
    case SHIP://
        rrow=r/10;
        srow=s/10;
        break;
    case BUS://
        rrow=r/4;
        srow=s/4;
        break;
    default:
        rrow=srow=0;
        break;
    }

    if(abs(rrow-srow)<=3){
        risk=3;
    }
    else if(abs(rrow-srow)<=7){
        risk=2;
    }
    else{
        risk=1;
    }
    return risk;
}
