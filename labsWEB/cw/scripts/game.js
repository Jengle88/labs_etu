import {GameManager} from "./GameManager.js";


const gameManager = new GameManager()
await gameManager.init()
// Нужно для первоначальной инициализации
const interval = setInterval(() => {gameManager.mapManager.draw(gameManager.canvas, gameManager.ctx)}, 10)
setTimeout(() => {clearInterval(interval)}, 100)

const startGameBtn = document.getElementById("game_start")
const restartGameBtn = document.getElementById("restart_game")

startGameBtn.addEventListener("click", async () => {
    if (!gameManager.allLevelFinished) {
        document.getElementById("game_start").style.visibility = "hidden"
        document.getElementById("restart_game").style.visibility = "visible"
        await gameManager.start()
    }
})

restartGameBtn.addEventListener("click", async () => {
    if (gameManager.isGameOver) {
        await gameManager.init()
        await gameManager.start()
    }
})

document.addEventListener("finishGame", () => {
    if (gameManager.allLevelFinished) {
        alert("Вы завершили все уровни")
    }
    if (gameManager.currScore >= GameManager.levelScores[gameManager.level]) {
        gameManager.level++
        alert("Открылся выход в нижнем правом углу")
    }
})

