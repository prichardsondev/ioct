//https://www.digi.com/resources/documentation/Digidocs/90002002/Content/Tasks/t_calculate_checksum.htm?TocPath=API%20Operation%7CAPI%20frame%20format%7C_____1
module.exports.calcXbeeCheckSum = function (data) {
    var checkSum = 0;
  
    for (let i = 3; i < data.length; i++)
      checkSum = checkSum + data[i];
  
    checkSum = (0xff - (checkSum & 0xff));
  
    return checkSum;
  }