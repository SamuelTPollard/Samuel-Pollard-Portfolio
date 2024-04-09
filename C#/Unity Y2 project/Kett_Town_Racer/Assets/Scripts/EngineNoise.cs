using UnityEngine;

public class EngineNoise : MonoBehaviour
{
    Rigidbody2D Car;
    AudioSource engineSound;
    public float Speed;
    AudioSource p;
    AudioClip Engine;
    AudioClip Hit;

    void Start()
    {
        Engine = Resources.Load<AudioClip>("Sound Effects/Engine");
        Hit = Resources.Load<AudioClip>("Sound Effects/Wall_Hit");
        p = gameObject.GetComponent<AudioSource>();
        Car = GetComponent<Rigidbody2D>();
        engineSound = GetComponent<AudioSource>();  
    }
    void Update()
    {
        engineSound.volume = Mathf.Clamp(Car.velocity.magnitude/ Speed, 0, 0.8f);
        engineSound.pitch =  -3 + (6 * Mathf.Clamp(Car.velocity.magnitude / Speed, 0, 1));
        if (!p.isPlaying)
        {
            p.clip = Engine;
            p.loop = true;
            p.Play();
        }
    }


    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (Car.velocity.magnitude > 2)
        {
            p.clip = Hit;
            p.Play();
            p.loop = false;
        }
    }
}
