/*
 * 1_base_trade_limit_entrust.h
 * 交易接口委托数据结构声明
 * created by 唐尚涛 
 */

#ifndef _BASE_TRADE_LIMIT_ENTRUST_H_
#define _BASE_TRADE_LIMIT_ENTRUST_H_

#include <stdint.h>
#include <stdint.h>
#include <string>
/*
 * 普通限价委托数据类型
 */
typedef enum 
{
    E_LONG,
    E_SHORT,

}base_trade_direction_type;                       // 交易方向类型
typedef enum
{
    E_OPEN,
    E_CLOSE,
    //E_CLOSE_TODAY,
    //E_CLOSE_YESTERDAY,

}base_trade_offset_type;                          // 交易开平类型

/*
 * 普通限价委托数据结构
 */
class base_trade_limit_entrust
{
public:
    // 交易所代码
    std::string exchange_code;
    // 期货合约代码
    std::string instrument_code;
    // 期货交易方向
    base_trade_direction_type direction;
    // 期货交易开平
    base_trade_offset_type offset;
    // 期货交易价格
    double limit_price;
    // 期货交易数量
    uint32_t volume;
    // 期货交易委托编号
    std::string entrust_id;
    // 委托发起者标识(用户自定义)
    std::string executor;
    
};




































#endif