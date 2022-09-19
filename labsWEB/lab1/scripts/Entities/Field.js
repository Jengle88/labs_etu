class Field {
    static tetraminos = ["OTetramino", "ITetramino", "STetramino", "ZTetramino", "LTetramino", "JTetramino", "TTetramino"]

    constructor(amountSquaresX, amountSquaresY) {
        this.width = amountSquaresX
        this.height = amountSquaresY
        this.score = 0
        this.field = []
        this.generateField(this.height, this.width);
    }

    generateField(height, width) {
        for (let i = 0; i < height; i++) {
            this.field.push([])
            for (let j = 0; j < width; j++) {
                this.field[i].push(UIEditor.clearElemColor)
            }
        }
    }

    setCurrTetramino() {
        this.currTetramino = this.nextTetramino
        return this.currTetramino.drawOnField(this.field)
    }

    generateNextTetramino() {
        let randomTetramino = Math.floor(Math.random() * 100) % Field.tetraminos.length
        // randomTetramino = 1
        let startX = this.width / 2
        let startY = 0
        if (Field.tetraminos[randomTetramino] !== "ITetramino") {
            startY = 0
        } else {
            startY = 1
        }
        switch (Field.tetraminos[randomTetramino]) {
            case "OTetramino":
                this.nextTetramino = new OTetramino(startX, startY)
                break
            case "ITetramino":
                this.nextTetramino = new ITetramino(startX, startY)
                break
            case "STetramino":
                this.nextTetramino = new STetramino(startX, startY)
                break
            case "ZTetramino":
                this.nextTetramino = new ZTetramino(startX, startY)
                break
            case "LTetramino":
                this.nextTetramino = new LTetramino(startX, startY)
                break
            case "JTetramino":
                this.nextTetramino = new JTetramino(startX, startY)
                break
            case "TTetramino":
                this.nextTetramino = new TTetramino(startX, startY)
                break
        }
    }

    moveCurrentTetraminoDown() {
        return this.currTetramino.moveDown(this.field)
    }

    moveCurrentTetraminoLeft() {
        return this.currTetramino.moveLeft(this.field)
    }

    moveCurrentTetraminoRight() {
        return this.currTetramino.moveRight(this.field)
    }

    rotateCurrentTetramino() {
        return this.currTetramino.rotateOnField(this.field)
    }

    removeFullLine() {
        let cntFullLine = 0
        let freeLines = []
        for (let currLineIndex = this.height-1; currLineIndex >= 0; currLineIndex--) {
            if (this.field[currLineIndex].find(item => item === UIEditor.clearElemColor) === undefined) {
                cntFullLine++
                for (let i = 0; i < this.width; i++) {
                    this.field[currLineIndex][i] = UIEditor.clearElemColor
                }
                freeLines.push(currLineIndex)
            } else if (this.field[currLineIndex].filter(it => it === UIEditor.clearElemColor).length !== this.field[currLineIndex].length) {
                if (freeLines.length !== 0) {
                    for (let i = 0; i < this.width; i++) {
                        this.field[freeLines[0]][i] = this.field[currLineIndex][i]
                        this.field[currLineIndex][i] = UIEditor.clearElemColor
                    }
                    freeLines.shift()
                    freeLines.push(currLineIndex)
                }
            }
        }
        return cntFullLine
    }
}