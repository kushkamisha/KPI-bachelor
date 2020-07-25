'use strict'

module.exports = {
    /**
     * Generates a random value according to an exponential distribution
     */
    randomExp: (timeMean=5) => {
        let num = 0
        while (num === 0) num = Math.random()
        return -timeMean * Math.log(num)
    },
    /**
     * Round a number to <precision> digits
     */
    round(num, precision) {
        return Math.round(num * 10 ** precision) / 10 ** precision
    }
}
