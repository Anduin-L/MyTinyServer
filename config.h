//
// Created by Anduin L on 16/12/2023.
//

#ifndef MYTINYSERVER_CONFIG_H
#define MYTINYSERVER_CONFIG_H

class Config {
public:
    Config();

    ~Config();

    // 解析方法
    void parse_arg(int argc, char *argv[]);

    // 端口号，默认3607
    int PORT;

    // 日志写入方式，默认同步
    int LOGWrite;

    /*
     * 触发组合模式 LT：水平触发 ET：边缘触发
     * 默认LT + ET
     *
     * LT(水平触发)
        当一个文件描述符上的事件就绪时，如果采用水平触发模式，内核会持续通知应用程序，直到这个事件被处理。
        即便应用程序没有完全处理当前事件，当下一次 epoll_wait 调用时，仍然会返回就绪状态，从而允许应用程序再次处理这个事件。
        LT 模式适用于慢速的、阻塞的 I/O 操作，因为它确保应用程序会在每次事件就绪时得到通知，不需要立即处理完事件。

     * ET(边缘触发)
        在边缘触发模式下，当文件描述符上的事件第一次就绪时，内核通知应用程序。然后，直到下次状态变化，它不会再次通知应用程序，即应用程序需要明确知道事件已经被处理，并且需要一次性地将缓冲区的数据读取完毕。
        如果应用程序没有读取完整个事件缓冲区，之后再调用 epoll_wait 也不会再次得到通知，除非有新的事件发生或者文件描述符的状态发生变化。
        ET 模式适用于高性能的、非阻塞的 I/O 操作，因为它允许应用程序有更多的控制权，只在需要时才进行事件处理。
     **/
    int TRIGModel;

    // listen fd触发模式，默认LT
    int LISTENTrigmode;

    // conn fd触发模式，默认LT
    int CONNTrigmode;

    // 优雅关闭链接，默认不使用
    int OPT_LINGER;

    // 线程数量，默认8
    int thread_num;

    // 关闭日志，默认不关闭
    int close_log;

    // 并发模型，默认proactor
    int actor_model;
};

#endif //MYTINYSERVER_CONFIG_H
