class Movable extends Placeable {
    constructor(xPos, yPos, currSpeed = 0) {
        super(xPos, yPos);
        this.currSpeed = currSpeed
    }

    move() {
        this.xPos += this.currSpeed
        this.yPos += this.currSpeed
    }
}

class Character extends Movable {
    constructor(xPos, yPos, currSpeed, health, damage) {
        super(xPos, yPos, currSpeed);
        this.health = health
        this.damage = damage
    }

    makeHit = (enemy) => {
        enemy.health -= this.damage
    }
}

class Hero extends Character {
    constructor(xPos, yPos, currSpeed = 3, health = 150, damage = 10, superDamage =  damage * 1.3) {
        super(xPos, yPos, currSpeed, health, damage);
        this.superDamage = superDamage
    }

    makeHit = (enemy, shouldSuperHit) => {
        enemy.health -= shouldSuperHit ? this.damage : this.superDamage
    }

    makeHeal(healObject) {
        this.health += healObject.healEffect
    }

}

class Enemy extends Character {

    constructor(xPos, yPos, currSpeed = 2, health = 100, damage = 7) {
        super(xPos, yPos, currSpeed, health, damage);
    }
}