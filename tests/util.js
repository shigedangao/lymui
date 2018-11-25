module.exports = {
  /**
   * To Fixed
   * 
   * @param {Object} n
   * @return {Object}
   */
  toFixed: o => {
    const keys = Object.keys(o)
    for (let idx = 0; idx < keys.length; idx++) {
      o[keys[idx]] = parseFloat(Number.parseFloat(o[keys[idx]]).toFixed(4))
    }

    return o;
  }
};