import {MapManager} from "./MapManager.js";
import {Enemy, Hero} from "./Characters.js";
import {HealObject} from "./GameObjects.js";
import {MovementManager} from "./MovementManager.js";
import {EventManager} from "./EventManager.js";
import {SpriteManager} from "./SpriteManager.js";
import {AudioManager} from "./AudioManager.js";

export class GameManager {

    static levelScores = {
        1: 400,
        2: 700
    }
    static scoreDeltas = {
        hit : 10,
        kill : 15
    }
    constructor() {
        this.audioManager = new AudioManager()
        this.mapManager = new MapManager(new SpriteManager())
        this.level = 1
        this.allLevelFinished = false
        this.isGameOver = false

        this.gameEndEvent = new CustomEvent("finishGame")
        this.clearMessage = new CustomEvent("clearMessage")

        this.scoreUpdateAndPrint = (delta) => {
            this.currScore += delta
            document.getElementById("player_score_value").innerText = ` ${this.currScore}`
        }

        this.levelPrinter = (level = this.level) => {
            document.getElementById("current_level_value").innerText = ` ${level}`
        }

        this.healthPrinter = (health = this.hero.health) => {
            document.getElementById("hero_health_value").innerText = `${ Math.max(health.toFixed(2), 0) }`
        }

        this.toNextLevel = async () => {
            if (this.allowNextLevel && this.mapManager.checkHeroNextToFinish()) {
                document.dispatchEvent(this.clearMessage)
                saveRecordToLeaderboard(localStorage["curr_player_name"], this.currScore)
                clearInterval(this.movementManager.heroAttackCoolDown)
                clearInterval(this.movementManager.movementChecker)
                clearInterval(this.movementManager.enemyAttackCoolDown)
                this.audioManager.pauseBackground(this.level)
                this.level++
                this.audioManager.playBackground(this.level)
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
            () => {
                if (!this.isGameOver && !this.allLevelFinished) {
                    this.movementManager.heroAttack(this.hero)
                    this.audioManager.playSound(AudioManager.gameSound.hitAudio)
                }
            },
            () => {
                if (!this.isGameOver && !this.allLevelFinished) {
                    let healPos = this.mapManager.checkHeroNextToHeal()
                    let heal = this.heals.find((heal) => { return heal.point === healPos })
                    if (heal)
                        this.movementManager.takeHeal(this.hero, heal)
                }
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
        this.isGameOver = false
        this.gameCycle = setInterval(() => {
            this.checkGameWon()
            this.checkEnemiesAlive()
            this.checkHeroAlive()
            this.tryMoveEnemies()
            this.mapManager.draw(this.canvas, this.ctx)
            this.checkGameOver()
        }, 30)
        this.audioManager.playBackground(this.level)
    }

    checkGameOver() {
        if (this.hero.health <= 0) {
            this.currScore = 0
            this.audioManager.playSound(AudioManager.gameSound.characterDeathAudio)
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
}