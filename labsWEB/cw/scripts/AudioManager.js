export class AudioManager {
    static gameSound = {
        hitAudio: "hurt_audio",
        characterDeathAudio: "character_death_audio"
    }

    constructor() {
        this.background1Audio = new Audio("audio/background1_audio.mp3")
        this.background2Audio = new Audio("audio/background2_audio.mp3")
        this.hitAudio = new Audio("audio/hit.wav")
        this.characterDeathAudio = new Audio("audio/character_death.wav")
        this.background1Audio.loop = true
        this.background2Audio.loop = true
    }

    playBackground(level) {
        switch (level) {
            case 1: this.background1Audio.play(); break;
            case 2: this.background2Audio.play(); break;
        }
    }

    pauseBackground(level) {
        switch (level) {
            case 1: this.background1Audio.pause(); break;
            case 2: this.background2Audio.pause(); break;
        }
    }

    playSound(audioName) {
        switch (audioName) {
            case AudioManager.gameSound.hitAudio: this.hitAudio.play(); break;
            case AudioManager.gameSound.characterDeathAudio: this.characterDeathAudio.play(); break;
        }
    }

    pauseSound(audioName) {
        switch (audioName) {
            case AudioManager.gameSound.hitAudio: this.hitAudio.pause(); break;
            case AudioManager.gameSound.characterDeathAudio: this.characterDeathAudio.pause(); break;
        }
    }

    pauseAll() {
        this.background1Audio.pause()
        this.background2Audio.pause()
        this.hitAudio.pause()
        this.characterDeathAudio.pause()
    }
}