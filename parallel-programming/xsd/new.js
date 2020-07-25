const fs = require('fs')
const xpath = require('xpath')
const dom = require('xmldom').DOMParser

const xml = fs.readFileSync('paper.xml', 'utf8')
const xmlPapers = xml.split('</Paper>\n')
const withoutHeader = xmlPapers[0].split('\n').slice(2)
xmlPapers[0] = `${withoutHeader}</Paper>`
xmlPapers.pop()

for (const xmlPaper of xmlPapers) {
    // console.log(`${xmlPaper}`)
    const doc = new dom().parseFromString(`${xmlPaper}</Paper>\n`)
    const nodes = xpath.select('//Paper', doc)

    const title = xpath.select("/Paper/Title/text()", nodes[0])[0].data
    const type = xpath.select("/Paper/Type/text()", nodes[0])[0].data
    const frequency = xpath.select("/Paper/Frequency/text()", nodes[0])[0].data
    const colorful = xpath.select("/Paper/Chars/Colorful/text()", nodes[0])[0].data
    const glossy = xpath.select("/Paper/Chars/Glossy/text()", nodes[0])[0].data
    const subIndex = xpath.select("/Paper/Chars/SubscribtionIndex/text()", nodes[0])[0].data

    const paper = {
        title, type, frequency,
        chars: { colorful, glossy, subIndex }
    }

    console.log({ paper })
}

/**
 * Select some data
 */
const doc = new dom().parseFromString(xml)
const titles = xpath.select('//Title', doc)
const colorful = xpath.select('/Catalog/Paper/Chars/Colorful[text()]', doc)
const volume = xpath.select(
    '/Catalog/Paper/Chars[Volume>100]/SubscribtionIndex', doc
)

for (const title of titles) {
    console.log(`${title.localName}: ${title.firstChild.data}`)
    // console.log("Node: " + titles[0].toString())
}

colorful.map(x => console.log(`${x.localName}: ${x.firstChild.data}`))
volume.map(x => console.log(`${x.localName}: ${x.firstChild.data}`))
