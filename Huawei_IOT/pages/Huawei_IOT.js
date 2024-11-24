// pages/Huawei_IOT.js
Page({

    /**
     * 页面的初始数据
     */
    data: {
        result:'等待获取token',
    },
    /**
     * 获取token按钮按下：
     */
    touchBtn_gettoken:function()
    {
        console.log("获取token按钮按下");
        this.setData({result:'获取token按钮按下'});
        this.gettoken();
    },
    /**
     * 获取设备影子按钮按下：
     */
    touchBtn_getshadow:function()
    {
        console.log("获取设备影子按钮按下");
        this.setData({result:'获取设备影子按钮按下'});
        this.getshadow();
    },
     /**
     * 设备命令下发按钮按下：
     */
    touchBtn_setCommand:function()
    {
        console.log("设备命令下发按钮按下");
        this.setData({result:'设备命令下发按钮按下，正在下发。。。'});
        this.setCommand();
    },  
    /**
     * 获取token
     */
    gettoken:function(){
        console.log("开始获取。。。");//打印完整消息
        var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
        wx.request({
            url: 'https://iam.cn-north-4.myhuaweicloud.com/v3/auth/tokens',
            data:'{"auth": { "identity": {"methods": ["password"],"password": {"user": {"name": "notus","password": "271233275nzy","domain": {"name": "hw067688473"}}}},"scope": {"project": {"name": "cn-north-4"}}}}',
            method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
            header: {'content-type': 'application/json' }, // 请求的 header 
            success: function(res){// success
              // success
                console.log("获取token成功");//打印完整消息
                console.log(res);//打印完整消息
                var token='';
                token=JSON.stringify(res.header['X-Subject-Token']);//解析消息头的token
                token=token.replaceAll("\"", "");
                console.log("获取token=\n"+token);//打印token
                wx.setStorageSync('token',token);//把token写到缓存中,以便可以随时随地调用
            },
            fail:function(){
                // fail
                console.log("获取token失败");//打印完整消息
            },
            complete: function() {
                // complete
                console.log("获取token完成");//打印完整消息
            } 
        });
    },
    /**
     * 获取设备影子
     */
    getshadow:function(){
        console.log("开始获取影子");//打印完整消息
        var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
        var token=wx.getStorageSync('token');//读缓存中保存的token
        wx.request({
            // url: 'https://iotda.cn-north-4.myhuaweicloud.com/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/shadow',
            url: 'https://628708ee2f.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/shadow',
            data:'',
            method: 'GET', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
            header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
            success: function(res){// success
            // success
                console.log(res);//打印完整消息
                var shadow=JSON.stringify(res.data.shadow[0].reported.properties);
                // var shadow=JSON.stringify(res.data.shadow[0]);
                console.log('设备影子数据：'+shadow);
                //以下根据自己的设备属性进行解析
                //我的设备影子：{"Temp":30,"temp":89,"Dev_data":77.20592,"humi":80,"light":3000,"GPS_N":3904.2279,"GPS_E":11706.2279,"warning":1,"MPU6050":1,"foot":12,"led":1,"temps":"89"}
                var Temp=JSON.stringify(res.data.shadow[0].reported.properties.temp);
                var Humi=JSON.stringify(res.data.shadow[0].reported.properties.humi);
                console.log('温度='+Temp+'℃');
                console.log('湿度='+Humi+'%');
                that.setData({result:'温度'+Temp+'℃,湿度'+Humi+'%'});
            },
            fail:function(){
                // fail
                console.log("获取影子失败");//打印完整消息
                console.log("请先获取token");//打印完整消息
            },
            complete: function() {
                // complete
                console.log("获取影子完成");//打印完整消息
            } 
        });
    },
    /**
     * 设备命令下发
     */
    setCommand:function(){
        console.log("开始下发命令。。。");//打印完整消息
        var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
        var token=wx.getStorageSync('token');//读缓存中保存的token
        wx.request({
            // url: 'https://iotda.cn-north-4.myhuaweicloud.com/v5/iot/786f139f-d7ef-4976-ae24-3f2e1d638de5/devices/674137332ff1872637c0d469_Device/commands',
            url: 'https://628708ee2f.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/commands',
            data:'{"service_id": "BasicData","command_name": "Control","paras": { "led": 1}}',
            method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
            header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
            success: function(res){// success
                // success
                console.log("下发命令成功");//打印完整消息
                console.log(res);//打印完整消息
                
            },
            fail:function(){
                // fail
                console.log("命令下发失败");//打印完整消息
                console.log("请先获取token");//打印完整消息
            },
            complete: function() {
                // complete
                console.log("命令下发完成");//打印完整消息
                that.setData({result:'设备命令下发完成'});
            } 
        });
    },

      
    /**
     * 生命周期函数--监听页面加载
     */
    onLoad(options) {

    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady() {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow() {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide() {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload() {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh() {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom() {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage() {

    }
})