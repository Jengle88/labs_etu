
export class MovementManager {

    constructor(mapManager) {
        this.mapManager = mapManager
    }

    moveCharacter(character, dir) {
        switch (dir) {
            case "a": character.currLRDir = "l"; break
            case "d": character.currLRDir = "r"; break
        }
        let newX = dir === "a" ? character.point.x - character.currSpeed : character.point.x
        newX = dir === "d" ? character.point.x + character.currSpeed : newX
        let newY = dir === "w" ? character.point.y - character.currSpeed : character.point.y
        newY = dir === "s" ? character.point.y + character.currSpeed : newY

        if (this.checkFreePath(newX, newY)) {
            character.point.x = newX
            character.point.y = newY
            return true
        } else
            return false
    }

    heroAttack(hero) {
        const dir = hero.currLRDir
        // TODO написать атаку игрока
    }

    moveEnemy(enemy, targetPos) {
        let imagineEnemyX = enemy.point.x - enemy.point.x % 2 
        let imagineTargetX = targetPos.x - targetPos.x % 2 
        let imagineEnemyY = enemy.point.y - enemy.point.y % 2 
        let imagineTargetY = targetPos.y - targetPos.y % 2 
        if (imagineEnemyX !== imagineTargetX || imagineEnemyY !== imagineTargetY) {
            if (imagineEnemyX < imagineTargetX)
                this.moveCharacter(enemy, "d")
            else if (imagineEnemyX > imagineTargetX)
                this.moveCharacter(enemy, "a")
            if (imagineEnemyY < imagineTargetY)
                this.moveCharacter(enemy, "s")
            else if (imagineEnemyY > imagineTargetY)
                this.moveCharacter(enemy, "w")
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