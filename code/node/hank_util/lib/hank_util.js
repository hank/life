function is_same_day(date1, date2) {
    return date1.getYear()  == date2.getYear()  &&
           date1.getMonth() == date2.getMonth() &&
           date1.getDay()   == date2.getDay();
}

function is_today(date) {
  return is_same_day(new Date(), date);
}

module.exports.is_today = is_today;
module.exports.is_same_day = is_same_day;
