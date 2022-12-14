import {MapManager, Point} from "./MapManager.js";
import {EventManager} from "./EventManager.js";

export class MovementManager {

    constructor(mapManager, eventManager) {
        this.mapManager = mapManager
        this.eventManager = eventManager
        this.movementChecker = setInterval(() => {
            if (this.eventManager.moveKeyBind[EventManager.keyToNum("w")].pressed) {
                this.moveCharacter(this.mapManager.hero, "w", true)
            }
            if (this.eventManager.moveKeyBind[EventManager.keyToNum("a")].pressed) {
                this.moveCharacter(this.mapManager.hero, "a", true)
            }
            if (this.eventManager.moveKeyBind[EventManager.keyToNum("s")].pressed) {
                this.moveCharacter(this.mapManager.hero, "s", true)
            }
            if (this.eventManager.moveKeyBind[EventManager.keyToNum("d")].pressed) {
                this.moveCharacter(this.mapManager.hero, "d", true)
            }
        }, 30)
        this.heroAttackCoolDown = setInterval(() => {
            let hero = this.mapManager.hero
            if (!hero.shouldAttack)
                return
            let upX = hero.point.x, upY = hero.point.y - this.mapManager.tileSize
            let downX = hero.point.x, downY = hero.point.y + this.mapManager.tileSize
            let dirX, dirY = hero.point.y
            if (hero.currLRDir === "l")
                dirX = hero.point.x - this.mapManager.tileSize
            else
                dirX = hero.point.x + this.mapManager.tileSize

            let attackedEnemies = []
            for (let i = 0; i < this.mapManager.enemiesPos.length; i++) {
                let enemyPos = this.mapManager.enemiesPos[i]
                if (this.#checkInTile(enemyPos, upX, upY) ||
                        this.#checkInTile(enemyPos, downX, downY) ||
                        this.#checkInTile(enemyPos, dirX, dirY)) {
                    attackedEnemies.push(this.mapManager.enemies[i])
                }
            }
            for (let i = 0; i < attackedEnemies.length; i++) {
                hero.makeHit(attackedEnemies[i], false)
            }
            setTimeout(() => {}, 100)
            hero.shouldAttack = false
        }, 300)
        this.enemyAttackCoolDown = setInterval(() => {
            for (let i = 0; i < this.mapManager.enemies.length; i++) {
                this.tryEnemyAttack(this.mapManager.enemies[i])
            }
        }, 400)
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
        hero.shouldAttack = true
    }

    takeHeal(hero, heal) {
        hero.makeHeal(heal)
        this.mapManager.removeHealFromField(heal.point)
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

    tryEnemyAttack(enemy) {
        let heroPos = this.mapManager.heroPos
        if (MapManager.getDist(
            new Point(heroPos.x + this.mapManager.tileSize / 2, heroPos.y + this.mapManager.tileSize / 2), // центр героя
            new Point(enemy.point.x + this.mapManager.tileSize / 2, enemy.point.y + this.mapManager.tileSize / 2) // центр врага
        ) <= MapManager.neededDistForEnemyAttack) {
            enemy.makeHit(this.mapManager.hero, false)
            if (this.mapManager.hero.health <= 0) {
                alert("Наш герой погиб!")
            }
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
        if (this.#isWall(luTileX, luTileY) || this.#isCharacter(luTileX, luTileY, shouldNotCheckHero, currentEnemy))
            return false
        // right up
        if (this.#isWall(ruTileX, ruTileY) || this.#isCharacter(ruTileX, ruTileY, shouldNotCheckHero, currentEnemy))
            return false
        // left down
        if (this.#isWall(ldTileX, ldTileY) || this.#isCharacter(ldTileX, ldTileY, shouldNotCheckHero, currentEnemy))
            return false
        // right down
        if (this.#isWall(rdTileX, rdTileY) || this.#isCharacter(rdTileX, rdTileY, shouldNotCheckHero, currentEnemy))
            return false
        return true
    }

    #isWall(x, y) {
        return this.mapManager.collisionPosition.find((wall) => { return wall.x <= x && x < wall.x + this.mapManager.tileSize &&
            wall.y <= y && y < wall.y + this.mapManager.tileSize })
    }
    #isCharacter(x, y, shouldNotCheckHero = false, currentEnemy = -1) {
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

    #checkInTile(enemyPos, x, y) {
        let positions = [
            /* lu */ new Point(x, y),
            /* ru */ new Point(x + this.mapManager.tileSize, y),
            /* ld */ new Point(x, y + this.mapManager.tileSize),
            /* rd */ new Point(x + this.mapManager.tileSize, y + this.mapManager.tileSize)
        ]
        for (let i = 0; i < positions.length; i++) {
            if ((enemyPos.x <= positions[i].x && positions[i].x <= enemyPos.x + this.mapManager.tileSize &&
                enemyPos.y <= positions[i].y && positions[i].y <= enemyPos.y + this.mapManager.tileSize)) {
                return true
            }
        }
        return false
    }
}