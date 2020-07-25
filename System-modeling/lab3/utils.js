'use strict'

module.exports = {
    /**
     * Generates a random value according to an exponential distribution
     */
    randomExp: (timeMean = 5) => {
        let num = 0
        while (num === 0) num = Math.random()
        return -timeMean * Math.log(num)
    },
    /**
     * Round a number to <precision> digits
     */
    round(num, precision=3) {
        return Math.round(num * 10 ** precision) / 10 ** precision
    },
    getRandomWithProbability(probs) {
        // If sum of probabilities is less than 1 - add new item, so that now
        // the sum would be 1
        const sumOfProbs = probs.reduce((acc, x) => acc += x)
        if (sumOfProbs < 1)
            probs.push(1 - sumOfProbs)

        const num = Math.random()
        let s = 0
        const lastIndex = probs.length -1

        for (let i = 0; i < lastIndex; ++i) {
            s += probs[i]
            if (num < s) {
                return i
            }
        }

        return lastIndex
    }
}
