class Field {
    static clearElemColor = "#00000020"
    static tetraminos = ["ITetramino", "OTetramino"]

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
                this.currTetramino.drawOnField(this.field)
                break
            case "ITetramino":
                this.currTetramino = new ITetramino(startX, startY)
                this.currTetramino.drawOnField(this.field)
                break
        }
    }

    clearField() {
        this.field = null
    }
}