
export class MovementManager {

    constructor(mapManager) {
        this.mapManager = mapManager
    }

    moveHero(hero, dir) {
        let newX = dir === "a" ? hero.point.x - hero.currSpeed : hero.point.x
        newX = dir === "d" ? hero.point.x + hero.currSpeed : newX
        let newY = dir === "w" ? hero.point.y - hero.currSpeed : hero.point.y
        newY = dir === "s" ? hero.point.y + hero.currSpeed : newY

        if (this.checkFreePath(newX, newY)) {
            hero.point.x = newX
            hero.point.y = newY
        }
    }

    checkFreePath(newX, newY) {
        // corners of hero tile
        let luTileX = newX
        let luTileY = newY
        let ruTileX = newX + this.mapManager.tileSize
        let ruTileY = newY
        let ldTileX = newX
        let ldTileY = newY + this.mapManager.tileSize
        let rdTileX = newX + this.mapManager.tileSize
        let rdTileY = newY + this.mapManager.tileSize

        // left up
        if (this.isWall(luTileX, luTileY))
            return false
        // right up
        if (this.isWall(ruTileX, ruTileY))
            return false
        // left down
        if (this.isWall(ldTileX, ldTileY))
            return false
        // right down
        if (this.isWall(rdTileX, rdTileY))
            return false
        return true
    }

    isWall(x, y) {
        return this.mapManager.collisionPosition.find((wall) => { return wall.x <= x && x < wall.x + this.mapManager.tileSize &&
            wall.y <= y && y < wall.y + this.mapManager.tileSize })
    }
}