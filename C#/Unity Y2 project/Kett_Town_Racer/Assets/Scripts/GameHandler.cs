using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;

public class GameHandler : MonoBehaviour
{
    GameObject Player;
    public int GameTime;
    public int BearTime;
    [SerializeField]
    int Score = 0;
    [HideInInspector]
    public int WaypointCount;
    public float remGTime;
    public float remBTime;
    [SerializeField]
    List<Transform> Waypoints = new();
    Text TimerText;
    Text ScoreText;
    
    void Start()
    {
        Player = GameObject.Find("Player");
        TimerText = GameObject.Find("Timer").GetComponent<Text>();
        ScoreText = GameObject.Find("Score").GetComponent<Text>();
        ScoreText.text = Score.ToString();
        remGTime = GameTime;
        remBTime = BearTime;
        GameObject Base = GameObject.Find("Waypoints");
        for (int i = 0; i < Base.transform.childCount; i++)
        {
            Waypoints.Add(Base.transform.GetChild(i));
        }
        WaypointCount = Waypoints.Count;
    }

    void Update()
    {
        if (!Player.GetComponent<WeetabixCarrying>().GetCarrying())
        {
            if (remGTime > 0)
            {
                remGTime -= Time.deltaTime;
                TimerText.text = ((int)remGTime).ToString();
            }
            else
            {
                string path = "Assets/Resources/" + gameObject.scene.name + ".txt";
                StreamReader fread = new StreamReader(path);
                int v = int.Parse(fread.ReadLine());
                fread.Close();
                if (v < Score)
                {
                    StreamWriter fwrite = new StreamWriter(path, false);
                    fwrite.WriteLine(Score);
                    fwrite.Close();
                    
                }
                Utilities.Loadscene("Menu");
            }
        }
        else
        {
            if (remBTime > 0)
            {
                remBTime -= Time.deltaTime;
                TimerText.text = ((int)remBTime).ToString();
            }
            else
            {
                Player.GetComponent<WeetabixCarrying>().DropWeetabix();
                remBTime = BearTime;
                AddScore(-50);
            }
        }
    }

    public void AddScore(int score)
    {
        Score += score;
        ScoreText.text = Score.ToString();
        remBTime = BearTime;
    }

    public Transform ClosestWaypoint(Transform Car)
    {
        return Utilities.ClosestInList(Car, Waypoints);
    }

    public Transform GetWaypoint(int index)
    {
        return Waypoints[index];
    }

    public int GetIndex(Transform Waypoint)
    {
        return Waypoints.IndexOf(Waypoint);
    }
}
