class GameCycle {
    constructor() {
        this.gameField = null
    }

    createField(width, height) {
        this.gameField = new Field(width, height)
        for (let i = 0; i < this.gameField.height && i < this.gameField.width; i++) {
            this.gameField.field[i][i] = "#1b77ce"
        }
    }

}


