const app = getApp();
Page({
  data: {
   temp:0,
   humi:0,
   light:0,
   result:'等待获取token',
   bttn_env:'开始环境检测',
   buttonClass: '',
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

  // 合一按钮
  // touchBtn_combine:function()
  // {
  //     console.log("开始进行环境检测");
  //     this.setData({result:'开始进行环境检测'});
  //     this.getenvdata();
  // },

  // getenvdata:function()
  // {
  //     this.gettoken();
  //     // setInterval(function(this.getshadow();
  //     setInterval(() => {
  //       this.getshadow();
  //     }, 3000);
  // },
  touchBtn_combine:function()
  {
    console.log("获取设备影子按钮按下");
    this.setData({result:'获取设备影子按钮按下'});
    this.gettoken();
    if (this.shadowInterval) {
        clearInterval(this.shadowInterval);
        this.shadowInterval = null;
        this.setData({result:'停止获取设备影子', bttn_env:'开始环境检测', buttonClass: ''});
    } else {
        this.getshadow();
        this.setData({bttn_env:'停止环境检测',buttonClass: 'clicked'})
        this.shadowInterval = setInterval(() => {
          this.getshadow();
        }, 1000);
    }
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
              // var date=JSON.stringify(res.data.shadow[0].reported.event_time);
              var date=JSON.stringify(res.header.Date);
              // var shadow=JSON.stringify(res.data.shadow[0]);
              console.log('设备影子数据：'+shadow);
              //以下根据自己的设备属性进行解析
              // var Temp=JSON.stringify(res.data.shadow[0].reported.properties.temp);
              // var Humi=JSON.stringify(res.data.shadow[0].reported.properties.humi);
              // console.log('温度='+Temp+'℃');
              // console.log('湿度='+Humi+'%');
              // that.setData({result:'温度'+Temp+'℃,湿度'+Humi+'%'});
              const temp = JSON.stringify(res.data.shadow[0].reported.properties.Temperature);
              const humi = JSON.stringify(res.data.shadow[0].reported.properties.Humidity);
              const light = JSON.stringify(res.data.shadow[0].reported.properties.Luminance);
              var lightstatus_tmp = JSON.stringify(res.data.shadow[0].reported.properties.LightStatus);
              if (lightstatus_tmp=='"OFF"'){
                lightstatus_tmp = "关";
              } else{
                lightstatus_tmp = "开";
              }
              const lightstatus = lightstatus_tmp;
              var motorstatus_tmp = JSON.stringify(res.data.shadow[0].reported.properties.MotorStatus);
              if (motorstatus_tmp=='"OFF"'){
                motorstatus_tmp = "关";
              } else{
                motorstatus_tmp = "开"
              }
              const motorstatus = motorstatus_tmp;
              that.setData({
                temp:temp,
                humi:humi,
                light:light,
                lightstatus:lightstatus,
                motorstatus:motorstatus,
              })
              if (app.globalData.messages.length >= 500)
                app.globalData.messages.pop();
              // console.log(app.globalData.messages.length);
              app.globalData.messages.push({"date":date, "temp":temp, "humi":humi, "light":light, "lightstatus":lightstatus, "motorstatus":motorstatus});
              
              app.globalData.flag_updated_message = true;
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
          // data:'{"service_id": "BasicData","command_name": "Control","paras": { "led": 1}}',
          data:'{"service_id": "BasicData","command_name": "Control_Light","paras": { "Light": "ON"}}',
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

  On_Light:function(){
      console.log("开始下发命令。。。");//打印完整消息
      var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
      var token=wx.getStorageSync('token');//读缓存中保存的token
      wx.request({
          // url: 'https://iotda.cn-north-4.myhuaweicloud.com/v5/iot/786f139f-d7ef-4976-ae24-3f2e1d638de5/devices/674137332ff1872637c0d469_Device/commands',
          url: 'https://628708ee2f.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/commands',
          // data:'{"service_id": "BasicData","command_name": "Control","paras": { "led": 1}}',
          data:'{"service_id": "BasicData","command_name": "Control_Light","paras": { "Light": "ON"}}',
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
          // complete: function() {
          //     // complete
          //     console.log("命令下发完成");//打印完整消息
          //     that.setData({result:'设备命令下发完成'});
          // } 
      });
  },
  
  Off_Light:function(){
      console.log("开始下发命令。。。");//打印完整消息
      var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
      var token=wx.getStorageSync('token');//读缓存中保存的token
      wx.request({
          // url: 'https://iotda.cn-north-4.myhuaweicloud.com/v5/iot/786f139f-d7ef-4976-ae24-3f2e1d638de5/devices/674137332ff1872637c0d469_Device/commands',
          url: 'https://628708ee2f.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/commands',
          // data:'{"service_id": "BasicData","command_name": "Control","paras": { "led": 1}}',
          data:'{"service_id": "BasicData","command_name": "Control_Light","paras": { "Light": "OFF"}}',
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
          // complete: function() {
          //     // complete
          //     console.log("命令下发完成");//打印完整消息
          //     that.setData({result:'设备命令下发完成'});
          // } 
      });
  },

  On_Motor:function(){
    console.log("开始下发命令。。。");//打印完整消息
    var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
    var token=wx.getStorageSync('token');//读缓存中保存的token
    wx.request({
        // url: 'https://iotda.cn-north-4.myhuaweicloud.com/v5/iot/786f139f-d7ef-4976-ae24-3f2e1d638de5/devices/674137332ff1872637c0d469_Device/commands',
        url: 'https://628708ee2f.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/commands',
        // data:'{"service_id": "BasicData","command_name": "Control","paras": { "led": 1}}',
        data:'{"service_id": "BasicData","command_name": "Control_Motor","paras": { "Motor": "ON"}}',
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
        // complete: function() {
        //     // complete
        //     console.log("命令下发完成");//打印完整消息
        //     that.setData({result:'设备命令下发完成'});
        // } 
    });
},

Off_Motor:function(){
    console.log("开始下发命令。。。");//打印完整消息
    var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
    var token=wx.getStorageSync('token');//读缓存中保存的token
    wx.request({
        // url: 'https://iotda.cn-north-4.myhuaweicloud.com/v5/iot/786f139f-d7ef-4976-ae24-3f2e1d638de5/devices/674137332ff1872637c0d469_Device/commands',
        url: 'https://628708ee2f.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/41a7f88585c547e49faf21cdb29f9955/devices/674137332ff1872637c0d469_Device/commands',
        // data:'{"service_id": "BasicData","command_name": "Control","paras": { "led": 1}}',
        data:'{"service_id": "BasicData","command_name": "Control_Motor","paras": { "Motor": "OFF"}}',
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
        // complete: function() {
        //     // complete
        //     console.log("命令下发完成");//打印完整消息
        //     that.setData({result:'设备命令下发完成'});
        // } 
    });
},
  
  kai:function(){
   //按钮发送命令控制硬件
    wx.request({
      url:"https://api.heclouds.com/cmds?device_id=106***2674",
      header: {
        'content-type': 'application/json',
        'api-key': apikey 
      },
      method: 'POST',
      data:{"LED0":1},
      success(res){
        console.log("成功",res.data)
      },
      fail(res){
        console.log("失败",res)
      }
    })
 },

 guan:function(){
 //按钮发送命令控制硬件
  wx.request({
    url:"https://api.heclouds.com/cmds?device_id=106***674",
    header: {
      'content-type': 'application/json',
      'api-key':apikey
    },
    method: 'POST',
    data:{"LED0":0},
    success(res){
      console.log("成功",res.data)
    },
    fail(res){
      console.log("失败",res)
    }
  })
},


  // onLoad() {
  //   var that = this
  //   setInterval(function(){
  //     that.getshadow()
  //   },3000000)
  // }
})
