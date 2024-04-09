using System.IO;
using UnityEngine;
using UnityEngine.UI;

public class GetHighScore : MonoBehaviour
{
    public string level;
    void Start()
    {
        try
        {
            string path = "Assets/Resources/" + level + ".txt";
            StreamReader fread = new StreamReader(path);
            string contents = fread.ReadToEnd();
            if (contents!= null)
            {  
                
                gameObject.GetComponent<Text>().text += " " + contents;
            }
            else
            {
                gameObject.GetComponent<Text>().text += " 0";
            }
        }
        catch(FileNotFoundException)
        {
            gameObject.GetComponent<Text>().text += " 0";
        }
    }


}
