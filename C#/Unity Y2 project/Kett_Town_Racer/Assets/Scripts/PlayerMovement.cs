using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public int DriveForce;
    public float TurnForce;
    Rigidbody2D Player;
    float moveVertical;
    float moveHorizontal;

    void Start()
    {
        Player = gameObject.GetComponent<Rigidbody2D>();
        Player.centerOfMass = new Vector2(0, 0.2f);
    }

    void FixedUpdate()
    {
        moveHorizontal = Input.GetAxis("Horizontal");
        moveVertical = Input.GetAxis("Vertical");
        Player.AddForce(DriveForce * moveVertical * transform.up);
        Player.AddTorque(TurnForce * -moveHorizontal * Mathf.Clamp(Player.velocity.magnitude / 12, -1, 1));
        Player.mass =  5 + (10 * Mathf.Clamp(Player.velocity.magnitude/12, 0, 1));
    }


}
  
