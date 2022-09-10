let gameCycle = null

class GameCycle {
    #keyListener;

    constructor() {
        this.gameField = null
        this.gameStatus = "pause"
        this.#keyListener = (event) => {
            const keyName = event.key
            if (this.gameStatus === "play") {
                switch (keyName) {
                    case "ArrowUp":
                        return
                    case "ArrowDown":
                        this.gameField.currTetramino.moveDown(this.gameField.field)
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowLeft":
                        this.gameField.currTetramino.moveLeft(this.gameField.field)
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowRight":
                        this.gameField.currTetramino.moveRight(this.gameField.field)
                        UIEditor.redrawTetrisField()
                        return
                }
            }
            if (keyName === " ") {
                if (this.gameStatus === "play") {
                    this.gameStatus = "pause"
                    this.pauseGame()
                } else {
                    this.gameStatus = "play"
                    this.startGame()
                }
            }
        }
        this.gameCycle = null

    }

    addKeyListener() {
        document.addEventListener('keydown', this.#keyListener)
    }

    createField(width, height) {
        this.gameField = new Field(width, height)
    }

    startGame() {
        let currThis = this
        this.gameCycle = new Promise(function (resolve, _) {
            // while (true) {
                if (currThis.gameStatus === "play") {
                    // TODO установка таймера для падения
                    currThis.gameField.generateTetramino()
                    UIEditor.redrawTetrisField()

                } else {
                    resolve()
                    return
                }
            // }
        }).then(function () {

        })



    }

    pauseGame() {

    }

    removeKeyListener() {
        document.removeEventListener('keydown', this.#keyListener)
    }
}


