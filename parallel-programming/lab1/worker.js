'use strict'

process.on('message', msg => {
    // console.log('[child] received message from server:', msg)

    let sumHoriz = 0
    for (let i = 0; i < msg.mtr.length; i++) {
        if (msg.i === i) continue
        sumHoriz += msg.mtr[msg.i][i]
    }

    let sumVert = 0
    for (let i = 0; i < msg.mtr.length; i++) {
        if (msg.i === i) continue
        sumVert += msg.mtr[i][msg.i]
    }

    process.send({ res: sumHoriz + sumVert })
})
