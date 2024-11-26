// pages/ctr/ctr.js
const app = getApp(); 
Page({

  /**
   * 页面的初始数据
   */
  data: {
    messages: [],
    hasMore: true,
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
  },

  updateMessages: function () {
    const that = this;
    setInterval(function () {
      // 从全局变量中获取消息，并更新页面数据
      that.setData({
        messages: app.globalData.messages,
      });
    }, 1000); // 每1000毫秒更新一次消息
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