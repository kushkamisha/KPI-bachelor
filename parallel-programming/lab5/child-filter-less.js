'use strict'

process.on('message', msg => {
    // console.log('[child] received message from server:', msg)
    let res = []
    for (let i = msg.start; i < msg.end; i++) {
        if (msg.arr[i] < msg.val) res.push(msg.arr[i])
    }
    process.send({ res })
});