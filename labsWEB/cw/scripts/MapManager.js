import {SpriteManager} from "./SpriteManager.js";

export class MapManager {

    static URL = "https://localhost:3000"
    static neededDist = 5 // TODO Исправить на нужное расстояние

    constructor() {
        this.spriteManager = new SpriteManager()
        this.tilesImages = {}
    }

    async init(level) {
        let response = await fetch(URL + `/level_data/${level}`)
        this.levelData = await response.json()
        this.fieldWidth = this.levelData["width"]
        this.fieldHeight = this.levelData["height"]
        this.tileSize = this.levelData["tileheight"]

        this.layerField = this.levelData["layers"][0]["data"]

        let finishLayer = this.levelData["layers"][1].find((layerData) => { return layerData.name === "finish" })
        let healPlacesLayer = this.levelData["layers"][1].find((layerData) => { return layerData.name === "heal_places" })
        let heroPlaceLayer = this.levelData["layers"][1].find((layerData) => { return layerData.name === "hero_place" })
        let enemyPlacesLayer = this.levelData["layers"][1].find((layerData) => { return layerData.name === "enemy_places" })

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
        this.healsPos = []
        this.healPositions.forEach((heal) => {
            this.healsPos.push(new HealObject(heal.x, heal.y))
        })

        this.tilesets = this.levelData["tilesets"]
    }

    draw(canvas, ctx) {
        // TODO написать функцию отрисовки
    }

    checkHeroNextToHeal() {
        this.healPositions.forEach((healPos) => {
            if (this.#getDist(this.heroPos, healPos) <= MapManager.neededDist)
                return true
        })
        return false
    }

    checkHeroNextToEnemy() {
        this.enemiesPos.forEach((enemyPos) => {
            if (this.#getDist(this.heroPos, enemyPos) <= MapManager.neededDist)
                return true
        })
        return false
    }

    checkHeroNextToFinish() {
        this.finishPositions.forEach((finishPos) => {
            if (this.#getDist(this.heroPos, finishPos) <= MapManager.neededDist)
                return true
        })
        return false
    }



    #getPositions(src, dest) {
        const width = this.fieldWidth / this.tileSize
        src.forEach((value, index) => {
            if (value !== 0) dest.push(new Point(index % width, index / width))
        })
        return dest
    }

    #getDist(point1, point2) {
        return Math.sqrt(Math.pow(point1.x - point2.x, 2) + Math.pow(point1.y - point2.y, 2))
    }

}

class Point {
    constructor(x, y) {
        this.x = x
        this.y = y
    }
}