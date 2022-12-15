import {GameManager} from "./GameManager.js";


const gameManager = new GameManager()
await gameManager.init()
// Нужно для первоначальной инициализации
const interval = setInterval(() => {gameManager.mapManager.draw(gameManager.canvas, gameManager.ctx)}, 10)
setTimeout(() => {clearInterval(interval)}, 100)

const startGameBtn = document.getElementById("game_start")
const restartGameBtn = document.getElementById("restart_game")
const gameMessage = document.getElementById("game_message")
document.getElementById("player_name").innerText = `Игрок: ${localStorage["curr_player_name"]}`

startGameBtn.addEventListener("click", async () => {
    document.getElementById("game_start").style.visibility = "hidden"
    document.getElementById("restart_game").style.visibility = "visible"
    gameMessage.innerText = ""
    await gameManager.start()
})

restartGameBtn.addEventListener("click", async () => {
    gameMessage.innerText = ""
    await gameManager.init()
    await gameManager.start()
})

document.addEventListener("finishGame", () => {
    if (gameManager.hero.health <= 0) {
        gameMessage.innerText = "Вы умерли"
        return
    }
    if (gameManager.allLevelFinished) {
        gameMessage.innerText = "Вы прошли все уровни"
        return
    }
    if (gameManager.currScore >= GameManager.levelScores[gameManager.level]) {
        gameMessage.innerText = "Открылся выход в правом нижнем углу. Дойдите до него и нажмите q"
        return
    }
})

document.addEventListener("clearMessage", () => {
        gameMessage.innerText = ""
    }
)
