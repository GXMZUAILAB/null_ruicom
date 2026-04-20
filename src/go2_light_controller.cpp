#include <iostream>
#include <unitree/robot/go2/vui/vui_client.hpp>
#include <unistd.h>
using namespace std;
int main()
{
    unitree::robot::ChannelFactory::Instance()->Init(0, "enx00e04c36141b");//enx00e04c36141b为网口号，用户根据自身情况修改
    unitree::robot::go2::VuiClient lc;
    lc.Init();
    usleep(500000); //不知道是否有时间功能
    int level = 5;
    if(lc.SetBrightness(level)==0)
    {
        cout<<"亮度设置成功"<<"当前亮度为"<<level<<endl;
    }
    else
    {
        cout<<"亮度设置失败"<<endl<<"错误码:"<<lc.SetBrightness(level)<<endl;
    }
    usleep(500000);//可以多次for循环上面的程序来使灯光闪烁，达成一定节目效果
        return 0;
}