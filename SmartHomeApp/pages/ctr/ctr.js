// log.js
const utils = require('../../utils/util.js');
const app = getApp(); // 获取全局变量

Page({
  data: {
    messages: [], // 页面数据，用于存储显示的消息
  },
  onLoad: function () {
    
  },
  onShow: function () {
    // 每次页面显示时更新消息
    this.updateMessages();
  },
  updateMessages: function () {
    const that = this;
    setInterval(function () {
      // 从全局变量中获取消息，并更新页面数据
      const flag = app.globalData.flag_updated_message;
      if(flag > 0){
        var updatedMessages = utils.sortTimes(app.globalData.messages);
        // updatedMessages = updatedMessages.map(time.date => utils.convertToCST(time.date))
        updatedMessages = updatedMessages.map(obj => {
          const date = utils.convertToCST(obj.date);
          return {
            "date": date, 
            "temp":obj.temp, "humi":obj.humi, "light":obj.light, "lightstatus":obj.lightstatus, "motorstatus":obj.motorstatus
          };
        });
        that.setData({
          messages: updatedMessages,
        });
        app.globalData.flag_updated_message = false;
        console.log(updatedMessages);
      }
    }, 1000); // 每1000毫秒更新一次消息
  },
  // 其他代码...
});