import {SpriteManager} from "./SpriteManager.js";

export class MapManager {

    static URL = "https://localhost:3000"
    static neededDistForEnemy = 100 // TODO Исправить на нужное расстояние
    static neededDistForObject = 25 // TODO Исправить на нужное расстояние

    constructor() {
        this.spriteManager = new SpriteManager()
    }

    async init(level) {
        let response = await fetch(MapManager.URL + `/level_data/${level}`)
        this.levelData = await response.json()
        this.fieldWidth = this.levelData["width"]
        this.fieldHeight = this.levelData["height"]
        this.tileSize = this.levelData["tileheight"]

        let finishLayer = this.levelData["layers"][1]["layers"].find((layerData) => { return layerData.name === "finish" })
        let healPlacesLayer = this.levelData["layers"][1]["layers"].find((layerData) => { return layerData.name === "heal_places" })
        let heroPlaceLayer = this.levelData["layers"][1]["layers"].find((layerData) => { return layerData.name === "hero_place" })
        let enemyPlacesLayer = this.levelData["layers"][1]["layers"].find((layerData) => { return layerData.name === "enemy_places" })

        // Points
        this.finishPositions = this.#getPositions(finishLayer["data"], [])
        this.healPositions = this.#getPositions(healPlacesLayer["data"], [])
        this.heroStartPosition = this.#getPositions(heroPlaceLayer["data"], [])
        this.enemiesStartPositions = this.#getPositions(enemyPlacesLayer["data"], [])
        this.collisionPosition = this.#getPositions(this.levelData["layers"][2]["data"], [])

        this.heroPos = new Point(this.heroStartPosition[0].x, this.heroStartPosition[0].y)
        this.enemiesPos = []
        this.enemiesStartPositions.forEach((enemy) => {
            this.enemiesPos.push(new Point(enemy.x, enemy.y))
        })

        this.tilesets = this.levelData["tilesets"]
    }

    setObjectsForDir(hero, enemies) {
        this.hero = hero
        this.enemies = enemies
    }

    draw(canvas, ctx) {
        ctx.clearRect(0, 0, canvas.width, canvas.height)

        ctx.drawImage(this.spriteManager.getSprite(SpriteManager.spritesName.level1Background), 0, 0)
        ctx.drawImage(this.spriteManager.getSprite(
            this.hero.currLRDir === "l" ? SpriteManager.spritesName.mainHeroL : SpriteManager.spritesName.mainHeroR
        ), this.heroPos.x, this.heroPos.y)
        this.enemies.forEach((enemy) => {
            ctx.drawImage(this.spriteManager.getSprite(
                enemy.currLRDir === "l" ? SpriteManager.spritesName.enemy1L : SpriteManager.spritesName.enemy1R
            ), enemy.point.x, enemy.point.y)
        })
        this.healPositions.forEach((healPos) => {
            ctx.drawImage(this.spriteManager.getSprite(SpriteManager.spritesName.heal1), healPos.x, healPos.y)
        })
    }

    checkHeroNextToHeal() {
        this.healPositions.forEach((healPos) => {
            if (this.#getDist(this.heroPos, healPos) <= MapManager.neededDistForObject)
                return healPos
        })
        return null
    }

    removeHealFromField(healPos) {
        let healIndex = this.healPositions.findIndex((heal) => { return heal.point === healPos })
        if (healIndex !== -1) {
            this.healPositions.splice(healIndex, 1)
        }
    }

    checkHeroNextToEnemy() {
        let enemies = []
        this.enemiesPos.forEach((enemyPos) => {
            if (this.#getDist(this.heroPos, enemyPos) <= MapManager.neededDistForEnemy)
                enemies.push(enemyPos)
        })
        return enemies
    }

    checkHeroNextToFinish() {
        this.finishPositions.forEach((finishPos) => {
            if (this.#getDist(this.heroPos, finishPos) <= MapManager.neededDistForObject)
                return true
        })
        return false
    }



    #getPositions(src, dest) {
        src.forEach((value, index) => {
            if (value !== 0) dest.push(new Point((index % this.fieldWidth) * this.tileSize, Math.floor(index / this.fieldWidth) * this.tileSize))
        })
        return dest
    }

    #getDist(point1, point2) {
        return Math.sqrt(Math.pow(point1.x - point2.x, 2) + Math.pow(point1.y - point2.y, 2))
    }

}

export class Point {
    constructor(x, y) {
        this.x = x
        this.y = y
    }
}