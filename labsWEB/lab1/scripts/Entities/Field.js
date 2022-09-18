class Field {
    static clearElemColor = "#00000020"
    static tetraminos = ["OTetramino", "ITetramino", "STetramino", "ZTetramino", "LTetramino", "JTetramino", "TTetramino"]

    constructor(amountSquaresX, amountSquaresY) {
        this.width = amountSquaresX
        this.height = amountSquaresY
        this.score = 0
        this.field = []
        this.currTetramino = null
        this.generateField(this.height, this.width);
    }

    generateField(height, width) {
        for (let i = 0; i < height; i++) {
            this.field.push([])
            for (let j = 0; j < width; j++) {
                this.field[i].push(Field.clearElemColor)
            }
        }
    }

    generateTetramino() {
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
                this.currTetramino = new OTetramino(startX, startY)
                break
            case "ITetramino":
                this.currTetramino = new ITetramino(startX, startY)
                break
            case "STetramino":
                this.currTetramino = new STetramino(startX, startY)
                break
            case "ZTetramino":
                this.currTetramino = new ZTetramino(startX, startY)
                break
            case "LTetramino":
                this.currTetramino = new LTetramino(startX, startY)
                break
            case "JTetramino":
                this.currTetramino = new JTetramino(startX, startY)
                break
            case "TTetramino":
                this.currTetramino = new TTetramino(startX, startY)
                break
        }
        return this.currTetramino.drawOnField(this.field)
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
            if (this.field[currLineIndex].find(item => item === Field.clearElemColor) === undefined) {
                cntFullLine++
                for (let i = 0; i < this.width; i++) {
                    this.field[currLineIndex][i] = Field.clearElemColor
                }
                freeLines.push(currLineIndex)
            } else if (this.field[currLineIndex].filter(it => it === Field.clearElemColor).length !== this.field[currLineIndex].length) {
                if (freeLines.length !== 0) {
                    for (let i = 0; i < this.width; i++) {
                        this.field[freeLines[0]][i] = this.field[currLineIndex][i]
                        this.field[currLineIndex][i] = Field.clearElemColor
                    }
                    freeLines.shift()
                    freeLines.push(currLineIndex)
                }
            }
        }
        return cntFullLine
    }

    removeCurrentTetramino() {
        return this.currTetramino.clearOnField(this.field, Field.clearElemColor)
    }
    clearField() {
        this.field = null
    }
}