'use strict'

process.on('message', msg => {
    // console.log('[child] received message from server:', msg)
    let sum = 0
    for (let i = msg.start; i < msg.end; i++) {
        sum += msg.arr[i]
    }
    process.send({ sum })
});