using UnityEngine;

public class TireTracks : MonoBehaviour
{
    [SerializeField]
    Rigidbody2D Player;
    void Start()
    {
        Player = GameObject.Find("Player").GetComponent<Rigidbody2D>();
    }

    void FixedUpdate()
    {
        gameObject.GetComponent<TrailRenderer>().emitting = false;
        if (Mathf.Abs(Player.angularVelocity) > 90)
        {
            gameObject.GetComponent<TrailRenderer>().emitting = true;
        }
    }
}
