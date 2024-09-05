

namespace MauiCalc;

public partial class MainPage : ContentPage
{
    public string CurrentInput { get; set; } = String.Empty;

    public string RunningTotal { get; set; } = String.Empty;

    private string selectedOperater;

    string[] operators = new string[] { "+", "-", "*", "/", "=" };

    string[] numbers = new string[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    bool resetOnNextInput = false;




    public MainPage()
    {
        InitializeComponent();
    }

    private void Button_Clicked(object sender, System.EventArgs e)
    {
        var btn = sender as Button;

        var thisInput = btn.Text;

        if (numbers.Contains(thisInput))
        {
            if (resetOnNextInput)
            {
                CurrentInput = btn.Text;
                resetOnNextInput = false;
            }
            else
            {
                CurrentInput += btn.Text;
            }

            LCD.Text = CurrentInput;
        }
        else if (operators.Contains(thisInput))
        {
            var result = PerformCalculation();

            if (thisInput == "=")
            {
                CurrentInput = result.ToString();

                LCD.Text = CurrentInput;

                RunningTotal = String.Empty;
                selectedOperater = String.Empty;

                resetOnNextInput = true;
            }
            else
            {
                RunningTotal = result.ToString();

                selectedOperater = thisInput;

                CurrentInput = String.Empty;

                LCD.Text = CurrentInput;
            }
        }
    }
    private double PerformCalculation()
    {
        double currentVal;
        double.TryParse(CurrentInput, out currentVal);

        double runningVal;
        double.TryParse(RunningTotal, out runningVal);

        double result;

        switch (selectedOperater)
        {
            case "+":
                result = currentVal + runningVal;
                break;
            case "-":
                result = currentVal - runningVal;
                break;
            case "*":
                result = currentVal * runningVal;
                break;
            case "/":
                result = currentVal / runningVal;
                break;
            default:
                result = currentVal;
                break;
        }
        return result;
    }
}