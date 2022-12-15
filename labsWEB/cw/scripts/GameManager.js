import {MapManager} from "./MapManager.js";
import {Enemy, Hero} from "./Characters.js";
import {HealObject} from "./GameObjects.js";
import {MovementManager} from "./MovementManager.js";
import {EventManager} from "./EventManager.js";

export class GameManager {

    static levelScores = {
        1: 10,
        2: 700
    }
    static scoreDeltas = {
        hit : 10,
        kill : 15
    }
    constructor() {

        this.mapManager = new MapManager()
        this.level = 1
        this.allLevelFinished = false
        this.isGameOver = false

        this.gameEndEvent = new CustomEvent("finishGame")
        this.clearMessage = new CustomEvent("clearMessage")

        this.scoreUpdateAndPrint = (delta) => {
            this.currScore += delta
            document.getElementById("player_score_value").innerText = ` ${this.currScore}`
        }

        this.levelPrinter = () => {
            document.getElementById("current_level_value").innerText = ` ${this.level}`
        }

        this.healthPrinter = (health) => {
            document.getElementById("hero_health_value").innerText = `${ Math.max(health.toFixed(2), 0) }`
        }

        this.toNextLevel = async () => {
            if (this.allowNextLevel && this.mapManager.checkHeroNextToFinish()) {
                document.dispatchEvent(this.clearMessage)
                saveRecordToLeaderboard(localStorage["curr_player_name"], this.currScore)
                clearInterval(this.movementManager.heroAttackCoolDown)
                clearInterval(this.movementManager.movementChecker)
                clearInterval(this.movementManager.enemyAttackCoolDown)
                await this.init()
            }
        }

        this.canvas = document.getElementById("game_field")
        this.ctx = this.canvas.getContext("2d")
    }

    async init() {
        this.currScore = 0
        this.allowNextLevel = false


        await this.mapManager.init(this.level)

        this.hero = new Hero(this.mapManager.heroPos)

        this.eventManager = new EventManager(
            () => { this.movementManager.heroAttack(this.hero) },
            () => {
                let healPos = this.mapManager.checkHeroNextToHeal()
                let heal = this.heals.find((heal) => { return heal.point === healPos })
                if (heal)
                    this.movementManager.takeHeal(this.hero, heal) // FIXME починить чётность пикселя при перемещении врага
            },
            this.toNextLevel
        )

        this.movementManager = new MovementManager(this.mapManager, this.eventManager, this.scoreUpdateAndPrint, this.healthPrinter)

        this.enemies = []
        this.mapManager.enemiesPos.forEach((enemyPos) => {
            this.enemies.push(new Enemy(enemyPos))
        })

        this.mapManager.setObjectsForDir(this.hero, this.enemies)

        this.heals = []
        this.mapManager.healPositions.forEach((healPos) => {
            this.heals.push(new HealObject(healPos))
        })

        this.levelPrinter()
        this.scoreUpdateAndPrint(0)
        this.healthPrinter(this.hero.health)

        this.ctx.canvas.width = this.mapManager.fieldWidth * this.mapManager.tileSize
        this.ctx.canvas.height = this.mapManager.fieldHeight * this.mapManager.tileSize
    }

    async start() {
        if (this.isGameOver) {
            await this.restartGame()
        }
        this.gameCycle = setInterval(() => {
            this.checkGameWon()
            this.checkEnemiesAlive()
            this.checkHeroAlive()
            this.tryMoveEnemies()
            this.mapManager.draw(this.canvas, this.ctx)
            this.checkGameOver()
        }, 30)
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
                case 1: {
                    this.allowNextLevel = true;
                    document.dispatchEvent(this.gameEndEvent)
                    break;
                }
                case 2: {
                    this.allLevelFinished = true;
                    this.finishGame()
                    break;
                }
            }
        }
    }

    finishGame() {
        this.isGameOver = true
        clearInterval(this.gameCycle)
        clearInterval(this.movementManager.heroAttackCoolDown)
        clearInterval(this.movementManager.movementChecker)
        clearInterval(this.movementManager.enemyAttackCoolDown)
        document.dispatchEvent(this.gameEndEvent)
        this.levelPrinter()
    }

    tryMoveEnemies() {
        const enemiesNextToHeroPos = this.mapManager.checkHeroNextToEnemy()
        this.enemies.forEach((enemy, index) => {
            if (enemiesNextToHeroPos.find((pos) => { return enemy.point === pos })) {
                this.movementManager.moveEnemy(enemy, index, this.hero.point)
            }
        })
    }

    checkEnemiesAlive() {
        for (let i = 0; i < this.enemies.length; i++) {
            if (this.enemies[i].health <= 0) {
                this.enemies.splice(i, 1)
                this.mapManager.enemiesPos.splice(i, 1)
            }
        }
    }

    checkHeroAlive() {
        if (this.mapManager.hero.health <= 0) {
            this.finishGame()
        }
    }

    async restartGame() {
        clearInterval(this.gameCycle)
        clearInterval(this.movementManager.heroAttackCoolDown)
        clearInterval(this.movementManager.movementChecker)
        clearInterval(this.movementManager.enemyAttackCoolDown)
        await this.init()
    }
}