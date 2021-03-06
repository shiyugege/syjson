#ifndef SYJSON_H__
#define SYJSON_H__

#include <stddef.h> // size_t
//数据类型
typedef enum {
	SYJSON_NULL, SYJSON_TRUE, SYJSON_FALSE, SYJSON_NUM, SYJSON_STR, SYJSON_ARR, SYJSON_OBJ
} syjson_type;

//值结构
typedef struct syjson_value syjson_value;
struct syjson_value
{
	syjson_type type; //元素类型
	union
	{
		struct {syjson_value* e;size_t s;} arr;  // 元素，数量
		struct {char* s; size_t l;} str;  //字符串指针，长度
		double num;  //浮点数
	} val; //元素值
};

//错误类型
enum {
	SYJSON_PARSE_OK = 0,
	SYJSON_PARSE_EXPECT_VALUE,
	SYJSON_PARSE_INVALID_VALUE,
	SYJSON_PARSE_ROOT_NOT_SINGULAR,
	SYJSON_PARSE_NUMBER_TOO_BIG,
	SYJSON_PARSE_MISS_QUOTATION_MARK,
	SYJSON_PARSE_INVALID_STRING_ESCAPE,
	SYJSON_PARSE_INVALID_STRING_CHAR,
	SYJSON_PARSE_INVALID_UNICODE_HEX,
	SYJSON_PARSE_INVALID_UNICODE_SURROGATE,
	SYJSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET
};

//json字符串--动态堆栈
typedef struct
{
	const char* json;
	char* stack;
	size_t size, top;
} syjson_content;

//初始化
#define syjson_init(v) do { (v)->type = SYJSON_NULL; } while(0)
//置空
#define syjson_set_null(v) syjson_free(v);
//解析函数
int syjson_parse(syjson_value* v, const char* json);
//清空数据
void syjson_free(syjson_value* v);
//获取json值类型
syjson_type syjson_get_type(const syjson_value* v);
//获取布尔值
int syjson_get_boolean(const syjson_value* v);
//设置布尔值
void syjson_set_boolean(syjson_value* v, int b);
//获取数字类型，防止不够用，使用double类型
double syjson_get_number(const syjson_value* v);
//设置数字
void syjson_set_number(syjson_value* v, double n);
//获取字符串
const char* syjson_get_string(const syjson_value* v);
//获取字符串长度
size_t syjson_get_string_length(const syjson_value* v);
//设置字符串
void syjson_set_string(syjson_value* v, const char* s, size_t l);
//获取数组大小
size_t syjson_get_array_size(const syjson_value* v);
//获取元素
syjson_value* syjson_get_array_element(const syjson_value* v, size_t index);

#endif
