import {Placeable} from "./GameObjects.js";

class Character extends Placeable {
    constructor(point, currSpeed, health, damage) {
        super(point);
        this.currSpeed = currSpeed
        this.health = health
        this.damage = damage
        this.currLRDir = "r"
        this.shouldAttack = false
    }

    makeHit = (enemy) => {
        enemy.health -= this.damage
    }
}

export class Hero extends Character {
    constructor(point, currSpeed = 7, health = 150, damage = 10, superDamage =  damage * 1.3) {
        super(point, currSpeed, health, damage);
        this.superDamage = superDamage
        this.currLRDir = "r"
    }

    makeHit = (enemy, shouldSuperHit) => {
        enemy.health -= shouldSuperHit ? this.damage : this.superDamage
    }

    makeHeal(healObject) {
        this.health += healObject.healEffect
    }

}

export class Enemy extends Character {
    constructor(point, currSpeed = 2, health = 50, damage = 7) {
        super(point, currSpeed, health, damage);
        this.shouldAttack = true
        this.currLRDir = (point.x / 13 + point.y / 13 * Math.random()) % 7 < 3 ? "r" : "l"
    }
}