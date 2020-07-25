'use strict'

const child_process = require('child_process')

const rand = (start, end) => Math.round(Math.random() * (end - start)) + start

const printMtr = mtr => {
    console.log()
    for (let i = 0; i < mtr.length; i++) {
        for (let j = 0; j < mtr.length; j++)
            process.stdout.write(`${mtr[i][j]} `)
        console.log()
    }
    console.log()
}

const n = 10
const mtr = new Array(n).fill().map(_ => new Array(n).fill().map(_ => rand(0, 9)))

printMtr(mtr)

const job = mtr => new Promise(resolve => {
    let done = 0
    for (let i = 0; i < mtr.length; i++) {
        const child = child_process.fork('./worker')

        child.send({ mtr, i })

        child.on('message', msg => {
            // console.log('[parent] received message from child:', msg)
            mtr[i][i] = msg.res
            done++
            if (done === mtr.length) resolve()
        })
    }
})

console.time('parallel')
job(mtr)
    .then(() => {
        console.timeEnd('parallel')
        printMtr(mtr)
        process.exit(0)
    })

console.time('sequential')
let sum = 0
for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
        if (i === j) continue
        sum += mtr[i][j] + mtr[j][i]
    }
    mtr[i][i] = sum
    sum = 0
}
console.timeEnd('sequential')

printMtr(mtr)
