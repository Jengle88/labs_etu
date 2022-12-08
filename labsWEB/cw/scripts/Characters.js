class Movable extends Placeable {
    constructor(point, currSpeed = 0) {
        super(point);
        this.currSpeed = currSpeed
    }

    move() {
        this.point.x += this.currSpeed
        this.point.y += this.currSpeed
    }
}

class Character extends Movable {
    constructor(point, currSpeed, health, damage) {
        super(point, currSpeed);
        this.health = health
        this.damage = damage
    }

    makeHit = (enemy) => {
        enemy.health -= this.damage
    }
}

class Hero extends Character {
    constructor(point, currSpeed = 3, health = 150, damage = 10, superDamage =  damage * 1.3) {
        super(point, currSpeed, health, damage);
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

    constructor(point, currSpeed = 2, health = 50, damage = 7) {
        super(point, currSpeed, health, damage);
    }
}