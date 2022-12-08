import {MapManager, Point} from "./MapManager.js";

export class GameManager {

    static levelScores = {
        1: 400,
        2: 700
    }
    constructor() {
        this.mapManager = new MapManager()
        this.level = 1
        this.currScore = 0
        this.allLevelFinished = false
        this.isGameOver = false
    }

    async init() {
        await this.mapManager.init(this.level)
        
        this.hero = new Hero(this.mapManager.heroPos)
        this.enemies = []
        this.mapManager.enemiesPos.forEach((enemyPos) => {
            this.enemies.push(new Enemy(enemyPos))
        })
        this.heals = []
        this.mapManager.healsPos.forEach((healPos) => {
            this.heals.push(new HealObject(healPos))
        })
        
        // TODO дописать настройку менеджеров
        this.canvas = document.getElementById("game_field")
        this.ctx = this.canvas.getContext("2d")

        this.ctx.canvas.width = this.mapManager.fieldWidth
        this.ctx.canvas.height = this.mapManager.fieldHeight
    }

    async start() {
        if (this.isGameOver) {
            await this.restartGame()
        }
    }

    checkHeal() {
        if (false) {

        }
        // TODO проверить наличие лечебного объекта
    }

    checkGameOver() {
        if (this.hero.health <= 0) {
            this.currScore = 0
            this.level = 1
            this.finishGame()
        }
    }

    checkGameWon() {
        if (this.currScore >= GameManager.levelScores[this.level]) {
            switch (this.level) {
                case 1: this.level++; break;
                case 2: this.allLevelFinished = true; break;
            }
            this.finishGame()
        }
    }

    finishGame() {
        this.isGameOver = true

        let gameEndEvent = new CustomEvent("finishGame")
        document.dispatchEvent(gameEndEvent)
    }

    async restartGame() {
        await this.init()
    }
}