class Field {
    static clearElemColor = "#00000020"
    static tetraminos = ["OTetramino", "ITetramino", "STetramino", "ZTetramino", "LTetramino", "JTetramino", "TTetramino"]

    constructor(amountSquaresX, amountSquaresY) {
        this.width = amountSquaresX
        this.height = amountSquaresY
        this.score = 0
        this.field = null
        this.currTetramino = null
        this.generateField(this.height, this.width);
    }

    generateField(height, width) {
        this.field = []
        for (let i = 0; i < height; i++) {
            this.field.push([])
            for (let j = 0; j < width; j++) {
                this.field[i].push(Field.clearElemColor)
            }
        }
    }

    generateTetramino() {
        let randomTetramino = Math.floor(Math.random() * 100) % Field.tetraminos.length
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
        this.currTetramino.drawOnField(this.field)
    }

    clearField() {
        this.field = null
    }
}