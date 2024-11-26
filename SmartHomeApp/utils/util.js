const formatTime = date => {
  const year = date.getFullYear()
  const month = date.getMonth() + 1
  const day = date.getDate()
  const hour = date.getHours()
  const minute = date.getMinutes()
  const second = date.getSeconds()

  return `${[year, month, day].map(formatNumber).join('/')} ${[hour, minute, second].map(formatNumber).join(':')}`
}

const formatNumber = n => {
  n = n.toString()
  return n[1] ? n : `0${n}`
}

// utils.js
// 用于转换时间的工具函数
function convertToCST(gmtTime) {
  const date = new Date(gmtTime);
  date.setHours(date.getHours()); // 将时间转换为中国标准时间
  const year = date.getFullYear();
  const month = (date.getMonth() + 1).toString().padStart(2, '0');
  const day = date.getDate().toString().padStart(2, '0');
  const hours = date.getHours().toString().padStart(2, '0');
  const minutes = date.getMinutes().toString().padStart(2, '0');
  const seconds = date.getSeconds().toString().padStart(2, '0');

  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
}

function convertToCST_cmp(gmtTime) {
  const date = new Date(gmtTime);
  date.setHours(date.getHours() + 8); // 将时间转换为中国标准时间

  return date;
}

function sortTimes(times) {
  return times.sort((a, b) => {
    const dateA = convertToCST_cmp(a.date);
    const dateB = convertToCST_cmp(b.date);
    return dateB - dateA; // 按照时间从晚到早排序
    // const dateA = convertToCST(a.date);
    // const dateB = convertToCST(b.date);
    // return dateA - dateB; // 按照时间从晚到早排序
  });
}

module.exports = {
  convertToCST,
  sortTimes,
  formatTime,
};



