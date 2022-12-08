import {GameManager} from "./GameManager.js";


const gameManager = new GameManager()
await gameManager.init()
// Нужно для первоначальной инициализации
// const interval = setInterval(() => {gameManager.mapManager.draw(gameManager.canvas, gameManager.ctx)}, 10)
// setTimeout(() => {clearInterval(interval)}, 100)

const startGameBtn = document.getElementById("game_start")

startGameBtn.addEventListener("click", async () => {
    if (!gameManager.allLevelFinished) {
        startGameBtn.disabled = true
        await gameManager.start()
    }
})

document.addEventListener("finishGame", () => {
    if (gameManager.allLevelFinished) {
        alert("Вы завершили все уровни")
    }
    if (gameManager.currScore >= GameManager.levelScores[gameManager.level]) {
        alert("Открылся выход в нижнем правом углу")
    }
})

