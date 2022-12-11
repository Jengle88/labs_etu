
export class MovementManager {

    constructor(mapManager) {
        this.mapManager = mapManager
    }

    moveCharacter(character, dir, shouldNotCheckHero, currentEnemy) {
        switch (dir) {
            case "a": character.currLRDir = "l"; break
            case "d": character.currLRDir = "r"; break
        }
        let newX = dir === "a" ? character.point.x - character.currSpeed : character.point.x
        newX = dir === "d" ? character.point.x + character.currSpeed : newX
        let newY = dir === "w" ? character.point.y - character.currSpeed : character.point.y
        newY = dir === "s" ? character.point.y + character.currSpeed : newY

        if (this.checkFreePath(newX, newY, shouldNotCheckHero, currentEnemy)) {
            character.point.x = newX
            character.point.y = newY
            return true
        } else
            return false
    }

    heroAttack(hero) {
        const dir = hero.currLRDir

    }

    moveEnemy(enemy, enemyNum, targetPos) {
        // Нужно, чтобы модели врагов не колебались от нечётности пикселя
        let imagineEnemyX = enemy.point.x - enemy.point.x % 2 
        let imagineTargetX = targetPos.x - targetPos.x % 2 
        let imagineEnemyY = enemy.point.y - enemy.point.y % 2 
        let imagineTargetY = targetPos.y - targetPos.y % 2 
        if (imagineEnemyX !== imagineTargetX || imagineEnemyY !== imagineTargetY) {
            if (imagineEnemyX < imagineTargetX)
                this.moveCharacter(enemy, "d", false, enemyNum)
            else if (imagineEnemyX > imagineTargetX)
                this.moveCharacter(enemy, "a", false, enemyNum)
            if (imagineEnemyY < imagineTargetY)
                this.moveCharacter(enemy, "s", false, enemyNum)
            else if (imagineEnemyY > imagineTargetY)
                this.moveCharacter(enemy, "w", false, enemyNum)
        }

    }

    checkFreePath(newX, newY, shouldNotCheckHero, currentEnemy) {
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
        if (this.isWall(luTileX, luTileY) || this.isCharacter(luTileX, luTileY, shouldNotCheckHero, currentEnemy))
            return false
        // right up
        if (this.isWall(ruTileX, ruTileY) || this.isCharacter(ruTileX, ruTileY, shouldNotCheckHero, currentEnemy))
            return false
        // left down
        if (this.isWall(ldTileX, ldTileY) || this.isCharacter(ldTileX, ldTileY, shouldNotCheckHero, currentEnemy))
            return false
        // right down
        if (this.isWall(rdTileX, rdTileY) || this.isCharacter(rdTileX, rdTileY, shouldNotCheckHero, currentEnemy))
            return false
        return true
    }

    isWall(x, y) {
        return this.mapManager.collisionPosition.find((wall) => { return wall.x <= x && x < wall.x + this.mapManager.tileSize &&
            wall.y <= y && y < wall.y + this.mapManager.tileSize })
    }
    isCharacter(x, y, shouldNotCheckHero = false, currentEnemy = -1) {
        let cnt = 0
        cnt += !shouldNotCheckHero && (this.mapManager.heroPos.x <= x && x <= this.mapManager.heroPos.x + this.mapManager.tileSize &&
            this.mapManager.heroPos.y <= y && y <= this.mapManager.heroPos.y + this.mapManager.tileSize)
        for (let i = 0; i < this.mapManager.enemiesPos.length; i++) {
            cnt += currentEnemy !== i &&
                (this.mapManager.enemiesPos[i].x <= x && x <= this.mapManager.enemiesPos[i].x + this.mapManager.tileSize &&
                this.mapManager.enemiesPos[i].y <= y && y <= this.mapManager.enemiesPos[i].y + this.mapManager.tileSize)
        }
        return cnt > 0
    }
}