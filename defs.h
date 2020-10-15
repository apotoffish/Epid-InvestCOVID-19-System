#ifndef DEFS_H
#define DEFS_H

#pragma once

#include <QString>
#include <QDate>

#define TRAIN 1//火车
#define FLIGHT 2//飞机
#define BUS 3//客车
#define SHIP 4//轮船

#define NOERROR 0
#define NOTRAFFIC -1
#define SEATERROR -2
#define LOCATIONERROR -3

#define TRAIN_MAX_SEAT 112
#define FLIGHT_MAX_SEAT 300
#define BUS_MAX_SEAT 56
#define SHIP_MAX_SEAT 800

#define TIPS "欢迎来到COVID-19 同乘接触者查询系统,使用本系统，请先阅读以下提示：\
\n在车次/班次编号中填入您的查询班次；\
\n在车厢号中填写火车车厢（其他无分隔交通工具均默认一舱） \
\n座位号中填写当天乘坐座位号\
\n在出发地和目的地中填写当天出行地点\
\n在右侧日历表中选择出发日期"

#define INPUTWRONG "输入错误"
#define TRAFFICWRONG "您输入的车次或日期有误，请核对后重新输入"
#define SEATWRONG "您输入的车厢或座位号无效，请核对后重新输入"
#define LOCATIONWRONG "您输入的行程区间有误，请核对后重新输入"
#define NORISK "您的查询结果为空，意味着截止目前为止，您没有在目标交通工具与新冠肺炎确诊患者有过密切接触"
#define LOWRISK "您的风险等级：低\n因为您曾与新冠肺炎确诊患者较短时间接触或座位距离较远。\n请遵照《国家传染病防治条例》，自觉上报当地卫生部门并在未来两周内随时关注自己的身体状况，期间如有发热、干咳等症状，立即避开人群前往附近发热门诊就诊并向本系统上报个人出行信息"
#define MEDIUMRISK "您的风险等级：中\n因为您曾与新冠肺炎确诊患者有一段时间接触或位于同一车厢舱室较短时间。\n请遵照《国家传染病防治条例》，自觉上报当地卫生部门并居家隔离14天，期间如有发热、干咳等症状，立即避开人群前往附近发热门诊就诊并向本系统上报个人出行信息"
#define HIGHRISK "您的风险等级：高\n因为您曾与新冠肺炎确诊患者有较长时间接触或位于患者附近座位。\n请遵照《国家传染病防治条例》，自觉上报当地卫生部门，接受新冠病毒核酸检测及定点隔离14天，并向本系统上报个人出行信息"

#define PROMISE "当前，新型冠状病毒感染的肺炎疫情防控形势严峻，作为居民群众，我践行我承诺：\
\n\n一、主动配合排查、对外来人员排查，做到早发现、早报告、早隔离、早治疗。发现异常情况及时向所在社区报告;曾经与疫情地区人员有往来的，或者出现发热、乏力、干咳或呼吸困难等症状的，主动向所在社区报告，并做好居家隔离工作。\
\n\n二、带头发挥作用、带头做到少外出少走动、不聚会不聚餐，避免到封闭、空气不流通的公众场所和人员密集场所。带头做好个人防护，正确使用口罩，推行移风易俗，保持良好的卫生习惯。带头参加党志愿服务活动，主动认领符合自身实际的宣传服务岗位。\
\n\n三、维护和谐稳定、带头不信谣不传谣，不道听途说，不以讹传讹，不散布虚假信息，自觉抵制谣言。带头学习防控知识，做好宣传引导和释疑解惑工作，不传播、不扩散非官方疫情消息。不哄抬物价、不哄抢商品，正规渠道购口罩，按需购买粮油，确保市场供应平稳、有序。"

struct finfo{
    int type;
    QString trafficNum;
    QString carriageNum;
    QString seatNum;
    QString departure;
    QString destination;
    QString date;
};

#endif // DEFS_H
