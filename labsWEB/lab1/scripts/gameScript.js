let gameCycle = null

class GameCycle {
    #keyListener;
    // #currTime;
    static #pauseTimeMS = 300
    static TAG = "gameScript"

    constructor() {
        this.gameField = null
        this.gameStatus = "pause"
        this.#keyListener = (event) => {
            const keyName = event.key
            if (this.gameStatus === "play" && this.gameField.currTetramino != null) {
                switch (keyName) {
                    case "ArrowUp":
                        this.gameField.rotateCurrentTetramino()
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowDown":
                        this.gameField.moveCurrentTetraminoDown()
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowLeft":
                        this.gameField.moveCurrentTetraminoLeft()
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowRight":
                        this.gameField.moveCurrentTetraminoRight()
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

    async startGame() {
        let currThis = this
        this.gameCycle = setInterval(() => {
            if (currThis.gameStatus === "play") {
                if (currThis.gameField.currTetramino == null) {
                    // генерация новой фигуры
                    if (!currThis.gameField.generateTetramino())
                        currThis.gameOver()
                    currThis.log("Тетрамина сгенерирована");
                } else { // есть фигура для снижения
                    if (!currThis.gameField.moveCurrentTetraminoDown()) {
                        currThis.gameField.removeFullLine()
                        currThis.gameField.currTetramino = null
                    }
                    currThis.log("Тетрамина опустилась вниз");
                }
                // возвращает количество удалённых строк
                UIEditor.redrawTetrisField()
            }
        }, GameCycle.#pauseTimeMS)
    }

    log(text) {
        console.log(`${GameCycle.TAG}: ${text}`)
    }

    pauseGame() {

    }

    gameOver() {
        alert("GameOver")
    }


    removeKeyListener() {
        document.removeEventListener('keydown', this.#keyListener)
    }
}


