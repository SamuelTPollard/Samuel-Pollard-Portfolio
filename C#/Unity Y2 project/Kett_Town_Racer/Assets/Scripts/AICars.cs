using UnityEngine;

public class AICars : MonoBehaviour
{
    Rigidbody2D rb;
    public float DriveForce;
    public float TurnForce;
    [SerializeField]
    bool Obstructed = false;
    int WaypointNum;
    GameHandler gameHandler;
    [SerializeField]
    Transform Target;
    void Awake()
    {
        GameObject Base = GameObject.Find("Waypoints");
        gameHandler = GameObject.Find("GameHandler").GetComponent<GameHandler>();
        rb = gameObject.GetComponent<Rigidbody2D>();
    }

    void FixedUpdate()
    {
        if (Target == null)
        {
            Target = gameHandler.ClosestWaypoint(gameObject.transform);
            WaypointNum = gameHandler.GetIndex(Target);
        }
        Vector3 relPos = (Target.position - transform.position); // Vector from player forward to next waypoint
        rb.AddTorque((TurnForce * Mathf.Clamp(Vector2.SignedAngle(transform.up, relPos), -1, 1)) * Mathf.Clamp(rb.velocity.magnitude/4, 0, 1));
        if (!Obstructed) 
        {
            rb.AddForce(DriveForce * Mathf.Clamp(Vector2.Distance(transform.position, Target.position)/5, 0.05f, 1) * transform.up);
        }
    }
   
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject == Target.gameObject)
        {
            WaypointNum++;
            if (WaypointNum == gameHandler.WaypointCount)
            {
                WaypointNum = 0;
            }
            Target = gameHandler.GetWaypoint(WaypointNum); 
        }
        if ((collision.CompareTag("Car") || collision.CompareTag("Player")) && Vector2.Dot(transform.up, collision.transform.position - transform.position) > 0.0f) // Only runs when a car enters from front trigger collider of the car
        {
            this.Obstructed = true;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.CompareTag("Car") || collision.CompareTag("Player"))
        {
            this.Obstructed = false;
        }
    }

}
