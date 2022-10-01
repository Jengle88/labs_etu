let gameCycle = null

class GameCycle {
    #keyListener;
    #pauseTimeMS;
    static TAG = "gameScript"
    static moveDownPlusScore = 30
    static removeOneLinePlusScore = 10
    static deltaPauseTime = 150
    // начиная с 3-го числа формула очков: [i-1] + ([i-1] - [i-2]) + 50, 13000 приведена как завершающая
    static nextLevelPoints = [150, 300, 500, 750, 1050, 1400, 1800, 2250, 2750, 3300, 3900, 4550, 5250, 6000, 6800, 7650, 8550, 9500, 10500, 13000]
    constructor() {
        this.gameField = null
        this.gameStatus = "pause"
        this.#pauseTimeMS = 500
        this.currLevel = 1
        let thisGameCycle = this
        this.gameScoreProxy = new Proxy( { score: 0 }, {
            set(target, p, value) {
                target[p] = value
                document.getElementById("player_score").textContent = `Счёт: ${value}`
                let index = GameCycle.nextLevelPoints.findIndex((valueLocal) => {
                    return valueLocal > value
                })
                if (index !== -1 && index + 1 > thisGameCycle.currLevel) {
                    thisGameCycle.levelUp(index + 1)
                }
                return true
            }
        })
        this.setKeyListener();
        this.gameCycle = null
    }

    createField(width, height) {
        this.gameField = new Field(width, height)
    }

    startGame() {
        if (!this.gameField.nextTetramino)
            this.gameField.generateNextTetramino()
        this.setTimerForTetraminos()
    }

    pauseGame() {
        clearInterval(this.gameCycle)
    }

    gameOver() {
        alert("GameOver")
        this.gameStatus = "gameover"
        this.pauseGame()
        saveRecordToLeaderboard(localStorage["curr_player_name"])
    }

    setTimerForTetraminos() {
        let thisGameCycle = this
        this.gameCycle = setInterval(() => {
            if (thisGameCycle.gameStatus === "play") {
                if (thisGameCycle.gameField.currTetramino == null) {
                    // генерация новой фигуры
                    if (!thisGameCycle.gameField.setCurrTetramino())
                        thisGameCycle.gameOver()
                    thisGameCycle.gameField.generateNextTetramino()
                    UIEditor.drawPreviewTetramino(this.gameField.nextTetramino)
                    thisGameCycle.log("Тетрамина сгенерирована");
                } else { // есть фигура для снижения
                    if (!thisGameCycle.gameField.moveCurrentTetraminoDown()) {
                        this.gameScoreProxy.score += thisGameCycle.gameField.removeFullLine() * GameCycle.removeOneLinePlusScore
                        thisGameCycle.gameField.currTetramino = null
                    }
                    thisGameCycle.log("Тетрамина опустилась вниз");
                }
                UIEditor.redrawTetrisField()
            }
        }, this.#pauseTimeMS)
    }

    levelUp(newLevel) {
        this.currLevel = newLevel
        this.#pauseTimeMS -= GameCycle.deltaPauseTime
        this.pauseGame()
        this.setTimerForTetraminos()
        document.getElementById("current_level").textContent = `Уровень: ${gameCycle.currLevel}`
        this.log(`Изменился уровень: ${newLevel}`)
    }

    setKeyListener() {
        this.#keyListener = (event) => {
            const keyName = event.key
            if (this.gameStatus === "play" && this.gameField.currTetramino != null) {
                switch (keyName) {
                    case "ArrowUp":
                        this.gameField.rotateCurrentTetramino()
                        UIEditor.redrawTetrisField()
                        return
                    case "ArrowDown":
                        if (this.gameField.moveCurrentTetraminoDown())
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
                        ScreenScript.toLeaderboardScreen()
                        break
                }

            }
        }
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


