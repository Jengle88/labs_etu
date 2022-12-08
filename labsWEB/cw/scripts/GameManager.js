import {MapManager} from "./MapManager.js";
import {Enemy, Hero} from "./Characters.js";
import {HealObject} from "./GameObjects.js";
import {MovementManager} from "./MovementManager.js";
import {EventManager} from "./EventManager.js";

export class GameManager {

    static levelScores = {
        1: 400,
        2: 700
    }
    constructor() {
        this.mapManager = new MapManager()
        this.movementManager = new MovementManager(this.mapManager)
        this.level = 1
        this.currScore = 0
        this.allLevelFinished = false
        this.isGameOver = false
    }

    async init() {
        await this.mapManager.init(this.level)
        
        this.hero = new Hero(this.mapManager.heroPos)

        this.eventManager = new EventManager()
        this.eventManager.setup(this.hero, this.movementManager)

        this.enemies = []
        this.mapManager.enemiesPos.forEach((enemyPos) => {
            this.enemies.push(new Enemy(enemyPos))
        })

        this.mapManager.setObjectsForDir(this.hero, this.enemies)

        this.heals = []
        this.mapManager.healPositions.forEach((healPos) => {
            this.heals.push(new HealObject(healPos))
        })
        
        // TODO дописать настройку менеджеров
        this.canvas = document.getElementById("game_field")
        this.ctx = this.canvas.getContext("2d")

        this.ctx.canvas.width = this.mapManager.fieldWidth * this.mapManager.tileSize
        this.ctx.canvas.height = this.mapManager.fieldHeight * this.mapManager.tileSize
    }

    async start() {
        if (this.isGameOver) {
            await this.restartGame()
        }
        this.gameCycle = setInterval(() => {
            this.checkGameWon()
            this.mapManager.draw(this.canvas, this.ctx)
            this.checkHeal()
            this.checkGameOver()
            this.hero.move(true)
        }, 30)
    }

    checkHeal() {
        let healPos = this.mapManager.checkHeroNextToHeal()
        if (healPos !== null) {
            let healObject = this.heals.find((heal) => {return heal.point === healPos})
            if (healObject !== undefined) {
                this.hero.makeHeal(healObject)
                this.mapManager.removeHealFromField(healPos)
                let healIndex = this.heals.findIndex((heal) => { return heal.point === healPos })
                if (healIndex === -1)
                    this.heals.splice(healIndex, 1)
            }
        }
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
        clearInterval(this.gameCycle)
        let gameEndEvent = new CustomEvent("finishGame")
        document.dispatchEvent(gameEndEvent)
    }

    async restartGame() {
        clearInterval(this.gameCycle)
        await this.init()
    }
}