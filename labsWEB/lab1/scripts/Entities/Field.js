class Field {
    static clearElemColor = "#00000020"

    constructor(amountSquaresX, amountSquaresY) {
        this.width = amountSquaresX
        this.height = amountSquaresY
        this.score = 0
        this.field = null
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

    clearField() {
        this.field = null
    }
}