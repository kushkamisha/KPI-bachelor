const RANDOM = { //returns random between -1 and 1
    'norm': function (n) {
        if (!(n > 2 && n <= 5)) n = 2
        var nrand = 0
        n = Math.floor(n)
        for (var i = 1; i <= n * 2; i++) {
            nrand += Math.random()
        }
        return (nrand - n) / n
    },
    'inorm': function (n) {
        if (!(n > 2 && n <= 5)) n = 2
        var nrand = 0
        n = Math.floor(n)
        for (var i = 1; i <= n * 2; i++) {
            nrand += Math.random()
        }
        return (1 - Math.abs((nrand - n) / n)) * (Math.abs(nrand - n) / (nrand - n))
    },
    'exp': function (n) { //mostly -1
        if (!(n > 2 && n <= 5)) n = 2
        var nrand = Math.random()
        for (var i = 2; i <= n; i++) {
            nrand *= Math.random()
        }
        return -(2 * nrand - 1)
    },
    'invexp': function (n) { //mostly 1
        if (!(n > 2 && n <= 5)) n = 2
        var nrand = Math.random()
        for (var i = 2; i <= n; i++) {
            nrand *= Math.random()
        }
        return (2 * (1 - nrand) - 1)
    },
    'gamma3': function (alpha) { //Kundu and Gupta algorithm 3 http://home.iitk.ac.in/~kundu/paper120.pdf
        if (!alpha || Math.abs(alpha) > 1) alpha = 1 //alpha between 0 and 1
        var d = 1.0334 - (0.0766 * Math.exp(2.2942 * alpha))
        var a = Math.pow(2, alpha) * Math.pow(1 - Math.exp(-d / 2), alpha)
        var b = alpha * Math.pow(d, alpha - 1) * Math.exp(-d)
        var c = a + b
        var U = Math.random()
        var X = (U <= a / (a + b)) ? -2 * Math.log(1 - (Math.pow(c * U, 1 / alpha) / 2)) : -Math.log(c * (1 - U) / (alpha * Math.pow(d, alpha - 1)))
        var V = Math.random()
        if (X <= d) {
            var mess = (Math.pow(X, alpha - 1) * Math.exp(-X / 2)) / (Math.pow(2, alpha - 1) * Math.pow(1 - Math.exp(-X / 2), alpha - 1))
            if (V <= mess) return X - 1
            else return this.gamma3(alpha)
        } else { //X > d
            if (V <= Math.pow(d / X, 1 - alpha)) return X - 1
            else return this.gamma3(alpha)
        }
        //output is > 0 and possibly > 1
    },
    'gamma': function (alpha, beta) { //Martino and Luengo http://arxiv.org/pdf/1304.3800.pdf luca@tsc.uc3m.es luengod@ieee.org
        if (!alpha || alpha <= 0) alpha = 1 //alpha >= 1 if negative or 0
        if (alpha > 0 && alpha < 1) return RANDOM.gamma3(alpha) // use different algorithm
        if (!beta || beta <= 0) beta = 1 //beta > 0
        var alphap = Math.floor(alpha)
        var X = Math.random()
        for (var i = 2; i <= alphap; i++) {
            X *= Math.random()
        }
        var betap = (alpha < 2) ? beta / alpha : beta * (alphap - 1) / (alpha - 1)
        X = -Math.log(X) / betap
        var Kp = (alpha < 2) ? Math.exp(1 - alpha) * Math.pow(alpha / beta, alpha - 1) : Math.exp(alphap - alpha) * Math.pow((alpha - 1) / beta, alpha - alphap)
        //then accept with prob p(X)/pi(X)
        if (alphap >= 2) {
            if (Kp * Math.pow(X, alphap - 1) * Math.exp(-betap * X) >= Math.pow(X, alpha - 1) * Math.exp(-beta * X)) return X / alpha - 1
            else return this.gamma(alpha, beta)
        }
        else if (alphap < 2) {
            if (Kp * Math.exp(-betap * X) >= Math.pow(X, alpha - 1) * Math.exp(-beta * X)) return X / alpha - 1
            else return this.gamma(alpha, beta)
        }
    },
    'igamma': function (alpha, beta) {
        return -RANDOM.gamma(alpha, beta)
    },
    'chi2': function (k) { // returns greater than 0
        var nrand = RANDOM.norm(2)
        nrand = nrand * nrand
        if (!k || k <= 1) return nrand - 1
        for (var i = 2; i <= k; i++) {
            var krand = RANDOM.norm(2)
            krand = krand * krand
            nrand += krand
        }
        return nrand - 1
    }
}

module.exports = {
    exp: RANDOM.exp,
    erlang: RANDOM.igamma
}
