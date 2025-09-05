#ifndef globals_H
#define globals_H


// 使用extern声明全局变量（不分配内存,不能初始化）
extern unsigned char now_str[7];
extern unsigned int now_str_loc;
extern unsigned char now;
extern unsigned char secret_user1[7];
extern unsigned char secret_user2[7];
extern unsigned char secret_user3[7];
extern unsigned char check_flag;
extern unsigned char paused_flag;
extern unsigned int paused_time;
extern bit paused_finish_flag;
extern unsigned char change_str[7];
extern unsigned int change_str_loc;
extern unsigned char change;

#endif