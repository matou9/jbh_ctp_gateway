/*
 * 0_future_limit_entrust.h
 * 期货限价委托类声明
 * created by 唐尚涛
 */
#ifndef _FUTURE_LIMIT_ENTRUST_H_
#define _FUTURE_LIMIT_ENTRUST_H_

#include <stdint.h>

/*
 * 普通限价委托数据类型
 */
typedef enum 
{
    E_LONG,
    E_SHORT,

}future_direction_type;                       // 交易方向类型
typedef enum
{
    E_OPEN,
    E_CLOSE,
    //E_CLOSE_TODAY,
    //E_CLOSE_YESTERDAY,

}future_offset_type;                          // 交易开平类型

/*
 * 普通限价委托数据结构
 * 参考CTP字段长度
 */
class future_limit_entrust
{
public:
    // 交易所代码
    char exchange_code[9];
    // 期货合约代码
    char instrument_code[31];
    // 期货交易方向
    future_direction_type direction;
    // 期货交易开平
    future_offset_type offset;
    // 期货交易价格
    double limit_price;
    // 期货交易数量
    uint32_t volume;
    // 期货交易委托编号
    char entrust_id[32];
    // 委托发起者标识(用户自定义)
    char executor[32];
    
};






















#endif