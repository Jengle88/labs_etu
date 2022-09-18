let gameCycle = null

class GameCycle {
    #keyListener;
    #pauseTimeMS;
    static TAG = "gameScript"
    static moveDownPlusScore = 2
    static removeOneLinePlusScore = 10

    constructor() {
        this.gameField = null
        this.gameStatus = "pause"
        this.#pauseTimeMS = 300
        this.gameScoreProxy = new Proxy( { score: 0 }, {
            set(target, p, value) {
                target[p] = value
                document.getElementById("player_score").textContent = `Счёт: ${value}`
                return true
            }
        })

        this.#keyListener = (event) => {
            const keyName = event.key
            if (this.gameStatus === "play" && this.gameField.currTetramino != null) {
                switch (keyName) {
                    case "ArrowUp":
                        this.gameField.rotateCurrentTetramino()
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowDown":
                        if(this.gameField.moveCurrentTetraminoDown())
                            this.gameScoreProxy.score = this.gameScoreProxy.score + GameCycle.moveDownPlusScore
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
                switch (this.gameStatus) {
                    case "play":
                        this.gameStatus = "pause"
                        this.pauseGame()
                        break
                    case "pause":
                        this.gameStatus = "play"
                        this.startGame()
                        break
                    case "gameover":
                        toStartScreen()
                        break
                }

            }
        }
        this.gameCycle = null
    }

    createField(width, height) {
        this.gameField = new Field(width, height)
    }

    startGame() {
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
                        this.gameScoreProxy.score += currThis.gameField.removeFullLine() * GameCycle.removeOneLinePlusScore
                        currThis.gameField.currTetramino = null
                    }
                    currThis.log("Тетрамина опустилась вниз");
                }
                // возвращает количество удалённых строк
                UIEditor.redrawTetrisField()
            }
        }, this.#pauseTimeMS)
    }

    pauseGame() {
        clearInterval(this.gameCycle)
    }

    gameOver() {
        alert("GameOver")
        this.gameStatus = "gameover"
        this.pauseGame()
    }

    addKeyListener() {
        document.addEventListener('keydown', this.#keyListener)
    }

    removeKeyListener() {
        document.removeEventListener('keydown', this.#keyListener)
    }

    log(text) {
        console.log(`${GameCycle.TAG}: ${text}`)
    }
}


