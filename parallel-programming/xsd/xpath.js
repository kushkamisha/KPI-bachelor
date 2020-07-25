const fs = require('fs')
const xpath = require('xpath')
    , dom = require('xmldom').DOMParser

const xml = fs.readFileSync('paper.xml', 'utf8')
console.log(xml.split('</Paper>\n')[1])
const doc = new dom().parseFromString(xml)

const nodes = xpath.select('//Paper', doc)
// const titles = xpath.select('//Title', doc)
// const colorful = xpath.select('/Catalog/Paper/Chars/Colorful[text()]', doc)
// const volume = xpath.select(
//     '/Catalog/Paper/Chars[Volume>100]/SubscribtionIndex', doc
// )
// console.log(papers[0])

// for (const title of titles) {
//     console.log(`${title.localName}: ${title.firstChild.data}`)
//     // console.log("Node: " + titles[0].toString())
// }

// colorful.map(x => console.log(`${x.localName}: ${x.firstChild.data}`))
// volume.map(x => console.log(`${x.localName}: ${x.firstChild.data}`))

// papers.map(x => console.log(`${x.localName}: ${x.firstChild.data}`))


// console.log(nodes[1])
// const title = xpath.select("/Catalog/Paper/Title/text()", nodes[1])[0].data
// const type = xpath.select("/Catalog/Paper/Type/text()", nodes[1])[0].data
// const frequency = xpath.select("/Catalog/Paper/Frequency/text()", nodes[1])[0].data
// const colorful = xpath.select("/Catalog/Paper/Chars/Colorful/text()", nodes[1])[0].data
// const glossy = xpath.select("/Catalog/Paper/Chars/Glossy/text()", nodes[1])[0].data
// const subIndex = xpath.select("/Catalog/Paper/Chars/SubscribtionIndex/text()", nodes[1])[0].data

// const paper = {
//     title, type, frequency,
//     chars: { colorful, glossy, subIndex }
// }

// console.log({ paper })

// const title = xpath.select("/Catalog/Paper/Title/text()", nodes[0])[0].data
// const type = xpath.select("/Catalog/Paper/Type/text()", nodes[0])[0].data
// const frequency = xpath.select("/Catalog/Paper/Frequency/text()", nodes[0])[0].data
// const colorful = xpath.select("/Catalog/Paper/Chars/Colorful/text()", nodes[0])[0].data
// const glossy = xpath.select("/Catalog/Paper/Chars/Glossy/text()", nodes[0])[0].data
// const subIndex = xpath.select("/Catalog/Paper/Chars/SubscribtionIndex/text()", nodes[0])[0].data

// const paper = {
//     title, type, frequency,
//     chars: { colorful, glossy, subIndex }
// }

// console.log({ paper })
